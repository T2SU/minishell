/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 00:24:41 by smun              #+#    #+#             */
/*   Updated: 2021/09/19 10:27:04 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include <stdlib.h>

char	*expand_variable(t_wordchunk *chunk)
{
	char	*ret;

	ret = NULL;
	if (chunk->flag == WordFlag_LastExitCode)
		return (ft_itoa(context_get()->laststatus));
	if (chunk->str != NULL && ft_strlen(chunk->str) > 0)
		ret = dict_get(context_get()->env, chunk->str);
	if (ret == NULL)
		ret = ft_strdup("");
	else
		ret = ft_strdup(ret);
	if (ret == NULL)
		exit_error();
	return (ret);
}

t_bool	is_single_dollar_sign(t_word *word)
{
	t_list		*lst;
	t_wordchunk	*chunk;

	lst = word->wordlist;
	if (lst == NULL)
		return (FALSE);
	chunk = lst->content;
	if (chunk->flag != WordFlag_DollarSign)
		return (FALSE);
	if (chunk->str == NULL || ft_strlen(chunk->str) > 0)
		return (FALSE);
	if (lst->next != NULL)
		return (FALSE);
	return (TRUE);
}

static void	concatenate_wordchunks(t_strbuf *strbuf, t_word *word,
									t_bool expand_vars)
{
	t_list		*lst;
	t_wordchunk	*chunk;
	char		*var;

	lst = word->wordlist;
	while (lst != NULL)
	{
		chunk = lst->content;
		if (!expand_vars && chunk->flag != WordFlag_None)
			strbuf_append(strbuf, '$');
		if (!expand_vars || chunk->flag == WordFlag_None)
			strbuf_appends(strbuf, chunk->str);
		else
		{
			var = expand_variable(chunk);
			strbuf_appends(strbuf, var);
			free(var);
		}
		lst = lst->next;
	}
}

char	*word_get(t_word *word, t_bool expand_vars, t_bool disposeword_after)
{
	t_strbuf	strbuf;

	ft_memset(&strbuf, 0, sizeof(t_strbuf));
	if (is_single_dollar_sign(word))
		strbuf_append(&strbuf, '$');
	else
		concatenate_wordchunks(&strbuf, word, expand_vars);
	if (disposeword_after)
	{
		ft_lstclear(&word->wordlist, &dispose_wordchunk);
		free(word);
	}
	return (strbuf_get(&strbuf));
}
