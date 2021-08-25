/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_install_redir.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 19:28:54 by smun              #+#    #+#             */
/*   Updated: 2021/08/25 20:27:19 by smun             ###   ########.fr       */
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
		// fileno fd를 복사해둠
		fd->stdfd = dup(fileno);
		// 리다이렉션 fd로 새로이 설정
		dup2(fd->fd, fileno);
	}
	else
	{
		// 리다이렉션 fd를 닫기
		close(fd->fd);
		// 복사해둔 fd를 다시 fileno로 복원
		dup2(fd->stdfd, fileno);
	}
}

void	execution_install_redir(t_execution *exec, t_bool enable)
{
	commit_redirection(&exec->in, STDIN_FILENO, enable);
	commit_redirection(&exec->out, STDOUT_FILENO, enable);
}
