/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 01:24:57 by smun              #+#    #+#             */
/*   Updated: 2021/08/25 19:39:58 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

t_bool	execution_set_redirection(t_execution *exec, int flags, int fd)
{
	if ((flags & kFileIn) && exec->in.fd != 0)
	{
		close(exec->in.fd);
		if (exec->heredoc != NULL)
		{
			unlink(exec->heredoc);
			free(exec->heredoc);
		}
		exec->heredoc = NULL;
	}
	if ((flags & kFileOut) && exec->out.fd != 0)
	{
		close(exec->out.fd);
	}
	if ((flags & kFileIn))
		exec->in.fd = fd;
	if ((flags & kFileOut))
		exec->out.fd = fd;
	return (fd != 0);
}

static void	print_redirection(const char *filename, t_redir *redir)
{
	if (!VERBOSE)
		return ;
	printf(BLUE" Redir Type : ");
	if (redir->type == kAppend)
		printf(RED"%s\n", "Append");
	if (redir->type == kRead)
		printf(RED"%s\n", "Read");
	if (redir->type == kReadHeredoc)
		printf(RED"%s\n", "ReadHeredoc");
	if (redir->type == kWrite)
		printf(RED"%s\n", "Write");
	printf(BLUE" FileName: "RED"%s"RESET"\n", filename);
}

static t_bool	handle_redirection(t_execution *exec, t_redir *redir)
{
	int		fd;
	char	*filename;
	t_bool	ret;

	if (redir->type == kReadHeredoc)
		filename = execution_make_heredoc(redir);
	else
		filename = word_get(redir->filename, TRUE, FALSE);
	if (filename == NULL)
		return (FALSE);
	fd = open(filename, redir->flags, 0644);
	if (fd == -1)
		ret = raise_system_error(filename);
	else if (redir->type == kRead || redir->type == kReadHeredoc)
		ret = execution_set_redirection(exec, kFileIn, fd);
	else if (redir->type == kWrite || redir->type == kAppend)
		ret = execution_set_redirection(exec, kFileOut, fd);
	else
		ret = raise_error(filename, "unknown redirection type");
	print_redirection(filename, redir);
	free(filename);
	return (ret);
}

t_bool	execution_handle_redirections(t_execution *exec)
{
	t_list		*lst;
	t_syntax	*syntax;

	syntax = exec->syntax;
	lst = syntax->redirs;
	while (lst != NULL)
	{
		if (!handle_redirection(exec, lst->content))
			return (execution_set_redirection(exec, kFileIn | kFileOut, 0));
		lst = lst->next;
	}
	return (TRUE);
}
