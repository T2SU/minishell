/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_make_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 20:54:12 by smun              #+#    #+#             */
/*   Updated: 2021/09/07 20:16:22 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	set_open_flags(int *flags, int type)
{
	if (type == kRead)
		*flags = O_RDONLY;
	if (type == kAppend)
		*flags = 0;
	if (type == kWrite)
		*flags = O_TRUNC | O_WRONLY | O_CREAT;
	if (type == kAppend)
		*flags = O_APPEND | O_WRONLY | O_CREAT;
}

void	syntax_make_redirection(t_stack *st, int type)
{
	t_word		*word;
	t_redir		*redir;
	t_list		*redirlst;

	word = syntax_strip(stack_pop(st), kWord);
	free(stack_pop(st));
	redir = safe_malloc(sizeof(t_redir));
	ft_memset(redir, 0, sizeof(t_redir));
	if (type == kReadHeredoc)
		redir->heredoc_eof = word_get(word, FALSE, TRUE);
	else
		redir->filename = word;
	redir->type = type;
	set_open_flags(&redir->flags, type);
	redirlst = ft_lstnew(redir);
	if (redirlst == NULL)
		exit_error();
	stack_push(st, syntax_make(redirlst, kRedir));
}

void	syntax_make_redirections(t_stack *st, t_syntax *next)
{
	t_syntax	*prev_syntax;
	t_list		*nextredir_lst;

	prev_syntax = stack_pop(st);
	nextredir_lst = syntax_strip(next, kRedir);
	ft_lstadd_back(&prev_syntax->redirs, nextredir_lst);
	stack_push(st, prev_syntax);
}

void	syntax_connect_redirection(t_stack *st, t_syntax *redir)
{
	t_syntax	*command;
	t_list		*redirs;

	command = stack_pop(st);
	redirs = syntax_strip(redir, kRedir);
	if (command->type == kConnection)
		ft_lstadd_back(&command->connect->second->redirs, redirs);
	else
		ft_lstadd_back(&command->redirs, redirs);
	stack_push(st, command);
}
