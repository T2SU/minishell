/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 23:42:45 by hkim              #+#    #+#             */
/*   Updated: 2021/08/29 16:00:37 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	compare_and_swap(t_list	*lst)
{
	size_t	key_len;
	t_pair	*tmp;

	key_len = ft_strlen(((t_pair *)lst->content)->key);
	if (key_len < ft_strlen(((t_pair *)lst->next->content)->key))
		key_len = ft_strlen(((t_pair *)lst->next->content)->key);
	if (ft_strncmp(((t_pair *)lst->content)->key,
			((t_pair *)lst->next->content)->key, key_len + 1) > 0)
	{
		tmp = (t_pair *)lst->content;
		lst->content = lst->next->content;
		lst->next->content = tmp;
	}
}

t_dict	*sort_dict(t_dict *dict)
{
	t_list	*lst;
	t_dict	*new_dict;
	int		size;
	int		i;
	int		j;

	new_dict = copy_dict(dict);
	lst = new_dict->head;
	size = ft_lstsize(lst);
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size - i - 1)
		{
			compare_and_swap(lst);
			lst = lst->next;
		}
		lst = new_dict->head;
	}
	return (new_dict);
}

int	find_equal(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			return (i);
	}
	return (-1);
}

void	print_export(void *content)
{
	t_pair	*tmp;
	char	*str;

	tmp = (t_pair *)content;
	printf("declare -x %s", tmp->key);
	if (tmp->equal)
	{
		printf("=\"");
		str = tmp->value;
		while (*str)
		{
			if (*str == '\\' || *str == '$' || *str == '"')
				printf("\\");
			printf("%c", *str);
			str++;
		}
		printf("\"");
	}
	printf("\n");
}
