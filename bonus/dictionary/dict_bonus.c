/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 01:50:42 by hkim              #+#    #+#             */
/*   Updated: 2021/09/19 01:50:42 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	dict_put(t_dict *dict, char *key, char *value, int equal)
{
	t_pair	*pair;

	if (dict_get(dict, key))
		dict_update(dict, key, value);
	else
	{
		pair = malloc(sizeof(t_pair));
		if (!pair)
			return (FALSE);
		pair->key = ft_strdup(key);
		if (value)
			pair->value = ft_strdup(value);
		else
			pair->value = ft_strdup("");
		pair->equal = equal;
		ft_lstadd_back(&dict->head, ft_lstnew(pair));
	}
	return (TRUE);
}

t_bool	del_first(t_dict *dict, char *key)
{
	t_list	*lst;

	lst = dict->head;
	if (!ft_strncmp(((t_pair *)lst->content)->key, key, ft_strlen(key) + 1))
	{
		dict->head = dict->head->next;
		free(((t_pair *)lst->content)->key);
		free(((t_pair *)lst->content)->value);
		free(((t_pair *)lst->content));
		free(lst);
		return (TRUE);
	}
	return (FALSE);
}

t_bool	dict_del(t_dict *dict, char *key)
{
	t_list	*lst;
	t_list	*next;
	t_pair	*pair;

	if (del_first(dict, key))
		return (TRUE);
	lst = dict->head;
	while (lst)
	{
		next = lst->next;
		pair = NULL;
		if (next != NULL)
			pair = (t_pair *)next->content;
		if (pair && !ft_strncmp(pair->key, key, ft_strlen(key) + 1))
		{
			lst->next = lst->next->next;
			free(pair->key);
			free(pair->value);
			free(pair);
			free(next);
			break ;
		}
		lst = lst->next;
	}
	return (TRUE);
}

void	dict_update(t_dict *dict, char *key, char *value)
{
	t_list	*lst;

	lst = dict->head;
	while (lst)
	{
		if (!ft_strncmp(((t_pair *)lst->content)->key, key, ft_strlen(key) + 1))
		{
			free(((t_pair *)lst->content)->value);
			((t_pair *)lst->content)->value = ft_strdup(value);
		}
		lst = lst->next;
	}
}

char	*dict_get(t_dict *dict, char *key)
{
	t_list	*lst;

	lst = dict->head;
	while (lst)
	{
		if (!ft_strncmp(((t_pair *)lst->content)->key, key, ft_strlen(key) + 1)
			&& ((t_pair *)lst->content)->equal)
			return (((t_pair *)lst->content)->value);
		lst = lst->next;
	}
	return (0);
}
