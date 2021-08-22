/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 01:00:53 by hkim              #+#    #+#             */
/*   Updated: 2021/08/22 13:47:11 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

t_dict	*copy_dict(t_dict *dict)
{
	t_dict	*new_dict;
	t_pair	*new_pair;
	t_list	*lst;

	new_dict = malloc(sizeof(t_dict));
	if (!new_dict)
		exit(1); // TODO : error;
	new_dict->head = NULL;
	lst = dict->head;
	while (lst)
	{
		new_pair = malloc(sizeof(t_pair));
		if (!new_pair)
			exit(1); // TODO : error;
		new_pair->key = ft_strdup(((t_pair *)lst->content)->key);
		new_pair->value = ft_strdup(((t_pair *)lst->content)->value);
		new_pair->equal = ((t_pair *)lst->content)->equal;
		ft_lstadd_back(&new_dict->head, ft_lstnew(new_pair));
		lst = lst->next;
	}
	return (new_dict);
}

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

/*
int	main(int argc, char **argv, char **envp)
{
	t_dict	*dict;
	t_list	*args;
	t_list	*add_list;

	argc = argc;
	argv = argv;
	dict = make_dict(envp);
	args = NULL;
	ft_lstadd_back(&args, ft_lstnew("USER"));
	run_unset(dict, args);
	add_list = NULL;
	ft_lstadd_back(&add_list, ft_lstnew("abc"));
	run_export(dict, add_list);
	run_export(dict, NULL);
	run_env(dict);
	dict_free(dict);
	free(args);
	free(add_list);
}
*/

/*
int	main(int argc, char **argv, char **envp)
{
	t_dict	*dict;
	t_list	*add_list;

	argc = argc;
	dict = make_dict(envp);
	add_list = NULL;
	ft_lstadd_back(&add_list, ft_lstnew(argv[1]));
	run_export(dict, add_list);
	run_export(dict, NULL);
	run_env(dict);
	dict_free(dict);
	free(add_list);
}
*/
