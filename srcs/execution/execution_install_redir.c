/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_install_redir.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 19:28:54 by smun              #+#    #+#             */
/*   Updated: 2021/09/12 17:28:24 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static void	commit_redirection(t_filedes *fd, int fileno, t_bool enable)
{
	if (fd->fd == 0)
		return ;
	if (enable)
	{
		fd->stdfd = dup(fileno);
		dup2(fd->fd, fileno);
	}
	else
	{
		dup2(fd->stdfd, fileno);
	}
}

void	execution_install_redir(t_execution *exec, t_bool enable)
{
	commit_redirection(&exec->in, STDIN_FILENO, enable);
	commit_redirection(&exec->out, STDOUT_FILENO, enable);
	if (!enable)
		execution_set_redir(exec, kFileIn | kFileOut, 0);
}
