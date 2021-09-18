/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 19:20:52 by smun              #+#    #+#             */
/*   Updated: 2021/09/19 01:49:59 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	check_chunk(t_strbuf *strbuf, t_wordchunk *chunk)
{
	char	*ch;

	if (chunk->quote == '\'' || chunk->quote == '\"')
	{
		ft_lstclear(&strbuf->head, &free);
		return (FALSE);
	}
	if (chunk->flag != WordFlag_None)
	{
		ch = expand_variable(chunk);
		strbuf_appends(strbuf, ch);
		free(ch);
	}
	else
		strbuf_appends(strbuf, chunk->str);
	return (TRUE);
}

t_bool	is_wildcard(t_word *word)
{
	t_strbuf	strbuf;
	t_list		*lst;
	char		*ch;
	t_bool		ret;

	if (word == NULL)
		return (FALSE);
	ft_bzero(&strbuf, sizeof(t_strbuf));
	lst = word->wordlist;
	while (lst != NULL)
	{
		if (!check_chunk(&strbuf, lst->content))
			return (FALSE);
		lst = lst->next;
	}
	ch = strbuf_get(&strbuf);
	ret = ft_strncmp(ch, "*", 2) == 0;
	free(ch);
	return (ret);
}
