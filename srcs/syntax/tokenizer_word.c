/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 22:51:30 by smun              #+#    #+#             */
/*   Updated: 2021/08/19 16:40:34 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	flush(t_word *word, t_strbuf *strbuf)
{
	t_wordchunk	*chunk;
	t_list		*lst;

	if (strbuf_length(strbuf) == 0)
		return (FALSE);
	chunk = safe_malloc(sizeof(t_wordchunk));
	lst = ft_lstnew(chunk);
	if (lst == NULL)
		exit_error();
	chunk->str = strbuf_get(strbuf);
	chunk->flag = WordFlag_None;
	ft_lstadd_back(&word->wordlist, lst);
	return (TRUE);
}

static void	parse_variable(t_word *word, t_strbuf *wsb, t_tokenizer *t)
{
	t_strbuf	strbuf;
	t_wordchunk	*chunk;
	t_list		*lst;

	flush(word, wsb);
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
	chunk->str = strbuf_get(&strbuf);
	ft_lstadd_back(&word->wordlist, lst);
}

static void	escape_char(t_tokenizer *t)
{
	const char	next = *(t->str + 1);

	if (t->quote != '\"')
		return ;
	if (next == '\"')
		t->str++;
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
		if (t->quote == 0 && ft_strchr(" \t<>&|()", *t->str))
			break ;
		if (ft_strchr("\'\"", *t->str)
			&& (t->quote == 0 || t->quote == *(t->str)))
		{
			t->quote ^= *(t->str++);
			if (flush(&word, &strbuf))
				continue ;
		}
		if (*t->str == '\\')
			escape_char(t);
		if (*t->str == '$')
			parse_variable(&word, &strbuf, t);
		else if (*t->str != '\0')
			strbuf_append(&strbuf, *(t->str++));
	}
	flush(&word, &strbuf);
	return (dup_word(&word));
}
