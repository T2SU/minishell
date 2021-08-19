/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose_property.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 13:46:05 by smun              #+#    #+#             */
/*   Updated: 2021/08/19 16:08:41 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void	dispose_redirection(void *ptr)
{
	t_redir	*redir;

	if (ptr == NULL)
		return ;
	redir = ptr;
	free(redir->heredoc_eof);
	dispose_word(redir->filename);
	free(redir);
}

static void	dispose_simplecmd(t_simplecmd *simplecmd)
{
	ft_lstclear(&simplecmd->args, &dispose_word);
	ft_lstclear(&simplecmd->redirs, &dispose_redirection);
	free(simplecmd);
}

static void	dispose_connection(t_connect *connect)
{
	dispose_syntax(connect->first);
	dispose_syntax(connect->second);
	free(connect);
}

static void	dispose_subshell(t_subshell *subshell)
{
	dispose_syntax(subshell->command);
	free(subshell);
}

void	dispose_syntax(void *ptr)
{
	t_syntax	*syntax;

	if (ptr == NULL)
		return ;
	syntax = (t_syntax *)ptr;
	if (syntax->type == kSimpleCommand)
		dispose_simplecmd(syntax->simplecmd);
	else if (syntax->type == kConnection)
		dispose_connection(syntax->connect);
	else if (syntax->type == kSubShell)
		dispose_subshell(syntax->subshell);
	else if (syntax->type == kWordList)
		ft_lstclear(&syntax->wordlist, &dispose_word);
	else if (syntax->type == kWord)
		dispose_word(syntax->word);
	ft_lstclear(&syntax->redirs, &dispose_redirection);
	ft_memset(syntax, 0, sizeof(t_syntax));
	free(ptr);
}
