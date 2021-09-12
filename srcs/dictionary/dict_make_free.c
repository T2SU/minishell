/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 10:23:21 by hkim              #+#    #+#             */
/*   Updated: 2021/08/25 10:23:21 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_key_value(char *str, t_pair **pair)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			(*pair)->key = ft_substr(str, 0, i);
			(*pair)->value = ft_substr(str, i + 1, ft_strlen(str) - i);
			(*pair)->equal = 1;
			break ;
		}
		i++;
	}
}

t_dict	*make_dict(char **envp)
{
	t_dict	*dict;
	t_pair	*pair;
	int		i;

	i = -1;
	dict = safe_malloc(sizeof(t_dict));
	dict->head = NULL;
	while (envp[++i])
	{
		pair = safe_malloc(sizeof(t_pair));
		save_key_value(envp[i], &pair);
		ft_lstadd_back(&dict->head, ft_lstnew(pair));
	}
	return (dict);
}

void	dict_free(t_dict *dict)
{
	t_list	*lst;
	t_list	*tmp;

	if (!dict)
		return ;
	lst = dict->head;
	while (lst)
	{
		free(((t_pair *)lst->content)->key);
		free(((t_pair *)lst->content)->value);
		free(((t_pair *)lst->content));
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
	free(dict);
}

t_dict	*copy_dict(t_dict *dict)
{
	t_dict	*new_dict;
	t_pair	*new_pair;
	t_list	*lst;

	new_dict = safe_malloc(sizeof(t_dict));
	new_dict->head = NULL;
	lst = dict->head;
	while (lst)
	{
		new_pair = safe_malloc(sizeof(t_pair));
		new_pair->key = ft_strdup(((t_pair *)lst->content)->key);
		new_pair->value = ft_strdup(((t_pair *)lst->content)->value);
		new_pair->equal = ((t_pair *)lst->content)->equal;
		ft_lstadd_back(&new_dict->head, ft_lstnew(new_pair));
		lst = lst->next;
	}
	return (new_dict);
}
