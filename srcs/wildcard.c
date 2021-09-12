/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:52:36 by smun              #+#    #+#             */
/*   Updated: 2021/09/12 17:22:20 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

static void	new_argument_entry(t_list **input, char *name)
{
	t_list	*lst;

	lst = ft_lstnew(ft_strdup(name));
	if (lst == NULL || lst->content == NULL)
		exit_error();
	ft_lstadd_back(input, lst);
}

static int	add_entries(DIR *dir, t_list **input)
{
	struct dirent	*dire;
	int				cnt;
	t_list			*templst;

	if (dir == NULL)
		return (0);
	cnt = 0;
	templst = NULL;
	while (TRUE)
	{
		dire = readdir(dir);
		if (dire == NULL)
			break ;
		if (dire->d_name[0] == '.')
			continue ;
		new_argument_entry(&templst, dire->d_name);
		cnt++;
	}
	ft_lstsort(templst, kAscending);
	if (*input == NULL)
		*input = templst;
	else
		ft_lstlast(*input)->next = templst;
	return (cnt);
}

void	expand_wildcard(t_list **input)
{
	DIR	*dir;
	int	cnt;

	dir = opendir(".");
	cnt = add_entries(dir, input);
	if (cnt == 0)
		new_argument_entry(input, "*");
	closedir(dir);
}

char	*get_single_filename(t_word *word)
{
	t_list	*lst;
	char	*arg;
	char	*ret;

	lst = NULL;
	expand_wildcard(&lst);
	if (ft_lstsize(lst) == 1)
	{
		ret = ft_strdup(lst->content);
		if (ret == NULL)
			exit_error();
	}
	else
	{
		arg = word_get(word, FALSE, FALSE);
		raise_error(arg, "ambiguous redirect");
		ret = NULL;
		free(arg);
	}
	ft_lstclear(&lst, &free);
	return (ret);
}
