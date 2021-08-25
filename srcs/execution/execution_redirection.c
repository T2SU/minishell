/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 01:24:57 by smun              #+#    #+#             */
/*   Updated: 2021/08/25 01:50:36 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

t_bool	execution_set_redirection(t_execution *exec, int flags, int fd)
{
	if ((flags & kFileIn) && exec->fd_in != 0)
	{
		close(exec->fd_in);
		if (exec->heredoc != NULL)
		{
			unlink(exec->heredoc);
			free(exec->heredoc);
		}
		exec->fd_in = fd;
		exec->heredoc = NULL;
	}
	if ((flags & kFileOut) && exec->fd_out != 0)
	{
		close(exec->fd_out);
		exec->fd_out = fd;
	}
	return (fd != 0);
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
		return (raise_system_error("unknown"));
	fd = open(filename, redir->flags);
	if (fd == -1)
		ret = raise_system_error(filename);
	else if (redir->type == kRead || redir->type == kReadHeredoc)
		ret = execution_set_redirection(exec, kFileIn, fd);
	else if (redir->type == kWrite || redir->type == kWrite)
		ret = execution_set_redirection(exec, kFileOut, fd);
	else
		ret = raise_error(filename, "unknown redirection type");
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
