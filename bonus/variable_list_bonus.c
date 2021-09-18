/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_list_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 19:20:12 by smun              #+#    #+#             */
/*   Updated: 2021/09/19 01:49:57 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_to_list(char *str, t_list **lst)
{
	t_list	*newlst;

	newlst = ft_lstnew(safe_strdup(str));
	if (newlst == NULL)
		exit_error();
	ft_lstadd_back(lst, newlst);
}

static void	iterate_variable_token(t_strbuf *strbuf, char *str, t_list **lst)
{
	char	*phrase;
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != ' ')
			strbuf_append(strbuf, str[i]);
		if (str[i] != ' ' || strbuf_length(strbuf) == 0)
			continue ;
		phrase = strbuf_get(strbuf);
		insert_to_list(phrase, lst);
		free(phrase);
	}
}

static void	iterate_chunks(t_strbuf *strbuf, t_wordchunk *chunk, t_list **lst)
{
	char	*str;

	if (chunk->quote)
		strbuf->flag |= SBFlag_ForceFlushing;
	if (chunk->flag == WordFlag_None)
	{
		strbuf_appends(strbuf, chunk->str);
		return ;
	}
	str = expand_variable(chunk);
	if (!ft_strchr(str, ' ') || chunk->quote)
	{
		strbuf_appends(strbuf, str);
		free(str);
		return ;
	}
	iterate_variable_token(strbuf, str, lst);
	free(str);
}

void	word_get_as_list(t_word *word, t_list **lst)
{
	t_strbuf	strbuf;
	t_list		*chunklst;
	char		*str;

	ft_bzero(&strbuf, sizeof(t_strbuf));
	chunklst = word->wordlist;
	while (chunklst)
	{
		iterate_chunks(&strbuf, chunklst->content, lst);
		chunklst = chunklst->next;
	}
	if ((strbuf.flag & SBFlag_ForceFlushing) == 0 && !strbuf_length(&strbuf))
		return ;
	str = strbuf_get(&strbuf);
	insert_to_list(str, lst);
	free(str);
}
