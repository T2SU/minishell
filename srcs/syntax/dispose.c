/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 13:46:05 by smun              #+#    #+#             */
/*   Updated: 2021/08/19 02:05:58 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	dispose_wordchunk(void *ptr)
{
	t_wordchunk	*wordchunk;

	if (ptr == NULL)
		return ;
	wordchunk = (t_wordchunk *)ptr;
	free(wordchunk->str);
	free(wordchunk);
}

void	dispose_token(void *ptr)
{
	t_token	*token;

	if (ptr == NULL)
		return ;
	token = (t_token *)ptr;
	if (token->type == kWord)
	{
		if (token->word)
			ft_lstclear(&token->word->wordlist, &dispose_wordchunk);
		free(token->word);
	}
	free(token);
}

void	dispose_word(void *ptr)
{
	t_word	*word;

	if (ptr == NULL)
		return ;
	word = (t_word *)ptr;
	ft_lstclear(&word->wordlist, &dispose_wordchunk);
	free(word);
}

void	dispose_redirection(void *ptr)
{
	t_redir	*redir;

	if (ptr == NULL)
		return ;
	redir = ptr;
	free(redir->heredoc_eof);
	dispose_word(redir->filename);
	free(redir);
}

void	dispose_syntax(void *ptr)
{
	t_syntax	*syntax;

	if (ptr == NULL)
		return ;
	syntax = (t_syntax *)ptr;
	if (syntax->type == kSimpleCommand)
	{
		ft_lstclear(&syntax->simplecmd->args, &dispose_word);
		ft_lstclear(&syntax->simplecmd->redirs, &dispose_redirection);
	}
	else if (syntax->type == kConnection)
	{
		dispose_syntax(syntax->connect->first);
		dispose_syntax(syntax->connect->second);
	}
	else if (syntax->type == kSubShell)
		dispose_syntax(syntax->subshell->command);
	free(ptr);
}
