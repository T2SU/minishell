/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:52:36 by smun              #+#    #+#             */
/*   Updated: 2021/09/01 15:26:11 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

t_bool	is_wildcard(t_word *word)
{
	t_strbuf	strbuf;
	t_list		*lst;
	t_wordchunk	*chunk;
	char		*ch;
	t_bool		ret;

	if (word == NULL)
		return (FALSE);
	ft_bzero(&strbuf, sizeof(t_strbuf));
	lst = word->wordlist;
	while (lst != NULL)
	{
		chunk = lst->content;
		if (chunk->quote == '\'' || chunk->quote == '\"')
		{
			ft_lstclear(&strbuf.head, &free);
			return (FALSE);
		}
		strbuf_appends(&strbuf, chunk->str);
		lst = lst->next;
	}
	ch = strbuf_get(&strbuf);
	ret = ft_strncmp(ch, "*", 2) == 0;
	free(ch);
	return (ret);
}

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
	struct dirent*	dire;
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

char	*get_single_filename(void)
{
	t_list	*lst;
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
		raise_error("*", "ambiguous redirect");
		ret = NULL;
	}
	ft_lstclear(&lst, &free);
	return (ret);
}
