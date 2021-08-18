/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 00:17:34 by smun              #+#    #+#             */
/*   Updated: 2021/08/19 00:34:06 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static void	print_word(t_word *word)
{
	t_wordchunk	*chunk;
	t_list		*lst;

	lst = word->wordlist;
	printf(CYAN"{ ");
	while (lst != NULL)
	{
		chunk = lst->content;
		if (chunk->flag == WordFlag_DollarSign)
			printf("$%s", chunk->str);
		else if (chunk->flag == WordFlag_LastExitCode)
			printf("$?");
		else
			printf("%s", chunk->str);
		lst = lst->next;
	}
	printf(CYAN"} ");
}

static void	print_redirection(t_list *lst)
{
	t_redir	*redir;

	while (lst != NULL)
	{
		redir = lst->content;
		if (redir->type == kRead)
		{
			printf(RED"< ");
			print_word(redir->filename);
		}
		if (redir->type == kWrite)
		{
			printf(RED"> ");
			print_word(redir->filename);
		}
		if (redir->type == kAppend)
		{
			printf(RED">> ");
			print_word(redir->filename);
		}
		if (redir->type == kReadHeredoc)
			printf(RED"<< {%s} ", redir->heredoc_eof);
		lst = lst->next;
	}
}

static void	print_simplecmd(t_simplecmd *simplecmd)
{
	t_list	*lst;

	printf(YELLOW"( ");
	lst = simplecmd->args->content;
	while (lst != NULL)
	{
		print_word(lst->content);
		lst = lst->next;
	}
	print_redirection(lst);
	printf(YELLOW")");
}

static void	print_connection(t_connect *con)
{
	syntax_print(con->first);
	if (con->connector == kPipe)
		printf(GREEN"| ");
	if (con->connector == kAnd)
		printf(GREEN"&& ");
	if (con->connector == kOr)
		printf(GREEN"|| ");
	syntax_print(con->second);
}

void	syntax_print(t_syntax *syntax)
{
	if (syntax == NULL)
		return ;
	if (syntax->type == kRedir)
		print_redirection(syntax->redirs);
	else if (syntax->type == kSimpleCommand)
		print_simplecmd(syntax->simplecmd);
	else if (syntax->type == kConnection)
		print_connection(syntax->connect);
	else if (syntax->type == kSubShell)
	{
		printf(BLUE"[ ");
		syntax_print(syntax->subshell->command);
		printf(BLUE"]");
	}
}
