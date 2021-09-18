/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_word_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 22:51:30 by smun              #+#    #+#             */
/*   Updated: 2021/09/19 01:51:37 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	flush_chunk(t_word *word, t_strbuf *sb, t_tokenizer *t, t_bool force)
{
	t_wordchunk	*chunk;
	t_list		*lst;

	if (strbuf_length(sb) == 0 && !force)
		return (FALSE);
	chunk = safe_malloc(sizeof(t_wordchunk));
	lst = ft_lstnew(chunk);
	if (lst == NULL)
		exit_error();
	chunk->str = strbuf_get(sb);
	chunk->flag = WordFlag_None;
	chunk->quote = 0;
	if (t != NULL)
		chunk->quote = t->quote;
	ft_lstadd_back(&word->wordlist, lst);
	return (TRUE);
}

static void	parse_variable(t_word *word, t_strbuf *wsb, t_tokenizer *t)
{
	t_strbuf	strbuf;
	t_wordchunk	*chunk;
	t_list		*lst;

	flush_chunk(word, wsb, t, FALSE);
	chunk = safe_malloc(sizeof(t_wordchunk));
	lst = ft_lstnew(chunk);
	if (lst == NULL)
		exit_error();
	ft_memset(&strbuf, 0, sizeof(t_strbuf));
	if (*(++t->str) == '?')
		chunk->flag = WordFlag_LastExitCode;
	else
		chunk->flag = WordFlag_DollarSign;
	if (chunk->flag == WordFlag_LastExitCode)
		strbuf_append(&strbuf, *(t->str++));
	else if (chunk->flag == WordFlag_DollarSign)
		while (*(t->str) && (ft_isalnum(*t->str) || *t->str == '_'))
			strbuf_append(&strbuf, *(t->str++));
	chunk->quote = t->quote;
	chunk->str = strbuf_get(&strbuf);
	ft_lstadd_back(&word->wordlist, lst);
}

t_word	*dup_word(t_word *ref)
{
	t_word	*ret;

	ret = safe_malloc(sizeof(t_word));
	*ret = *ref;
	return (ret);
}

t_word	*get_word(t_tokenizer *t)
{
	t_word		word;
	t_strbuf	strbuf;

	ft_memset(&strbuf, 0, sizeof(t_strbuf));
	ft_memset(&word, 0, sizeof(t_word));
	while (*t->str != '\0')
	{
		if (t->quote == 0 && ft_strchr(" \t\n\r<>&|()", *t->str))
			break ;
		if (ft_strchr("\'\"", *t->str)
			&& (t->quote == 0 || t->quote == *(t->str)))
		{
			flush_chunk(&word, &strbuf, t, t->quote != 0);
			t->quote ^= *(t->str++);
			continue ;
		}
		if (*t->str == '$' && t->quote != '\'')
			parse_variable(&word, &strbuf, t);
		else if (*t->str != '\0')
			strbuf_append(&strbuf, *(t->str++));
	}
	flush_chunk(&word, &strbuf, t, word.wordlist == NULL);
	return (dup_word(&word));
}
