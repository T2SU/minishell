/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 10:29:26 by hkim              #+#    #+#             */
/*   Updated: 2021/08/25 10:29:26 by hkim             ###   ########.fr       */
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
			((t_pair *)lst->next->content)->key, key_len) > 0)
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

void	run_export_with_args(t_dict *dict, t_list *args)
{
	char	*str;
	char	*key;
	char	*value;
	int		idx;

	while (args)
	{
		str = (char *)args->content;
		idx = find_equal(str);
		if (idx == -1)
		{
			key = ft_strdup(str);
			value = ft_strdup("");
			dict_put(dict, key, value, 0);
		}
		else
		{
			key = ft_substr(str, 0, idx);
			value = ft_substr(str, idx + 1, ft_strlen(str) - idx);
			dict_put(dict, key, value, 1);
		}
		free(key);
		free(value);
		args = args->next;
	}
}

t_bool	run_export(t_dict *dict, t_list *args)
{
	t_dict	*new_dict;

	if (dict == NULL)
		return (FALSE);
	if (args == NULL)
	{
		new_dict = sort_dict(dict);
		ft_lstiter(new_dict->head, &print_export);
		dict_free(new_dict);
	}
	else
		run_export_with_args(dict, args);
	return (TRUE);
}
