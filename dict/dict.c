/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 15:06:30 by hkim              #+#    #+#             */
/*   Updated: 2021/08/21 01:27:48 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

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
	dict = malloc(sizeof(t_dict));
	if (!dict)
		exit(1); // TODO : print proper error message
	dict->head = NULL;
	while (envp[++i])
	{
		pair = malloc(sizeof(t_pair));
		if (!pair)
			exit(1); // TODO : print proper error message
		save_key_value(envp[i], &pair);
		ft_lstadd_back(&dict->head, ft_lstnew(pair));
	}
	return (dict);
}

t_bool	dict_put(t_dict *dict, char *key, char *value)
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
		pair->value = ft_strdup(value);
		ft_lstadd_back(&dict->head, ft_lstnew(pair));
	}
	return (TRUE);
}

t_bool	del_first(t_dict *dict, char *key)
{
	t_list	*lst;

	lst = dict->head;
	if (!ft_strncmp(((t_pair *)lst->content)->key, key, ft_strlen(key)))
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

	if (del_first(dict, key))
		return (TRUE);
	lst = dict->head;
	while (lst)
	{
		next = lst->next;
		if (next != NULL
			&& !ft_strncmp(((t_pair *)next->content)->key, key, ft_strlen(key)))
		{
			lst->next = lst->next->next;
			free(((t_pair *)next->content)->key);
			free(((t_pair *)next->content)->value);
			free(((t_pair *)next->content));
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
		if (!ft_strncmp(((t_pair *)lst->content)->key, key, ft_strlen(key)))
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
		if (!ft_strncmp(((t_pair *)lst->content)->key, key, ft_strlen(key)))
			return (((t_pair *)lst->content)->value);
		lst = lst->next;
	}
	return (0);
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

// int	main(int argc, char **argv, char **envp)
// {
// 	t_dict	*dict;
// 	char	*ans;

// 	dict = make_dict(envp);
// 	dict_put(dict, "abc", "def");
// 	ans = dict_get(dict, "abc");
// 	if (!ans)
// 	{
// 		printf("error\n");
// 		dict_free(dict);
// 		return (1);
// 	}
// 	printf("%s\n", ans);
// 	dict_del(dict, "abc");
// 	dict_put(dict, "USER", "fake_user");
// 	run_env(dict);
// 	dict_free(dict);
// 	return (0);
// }
