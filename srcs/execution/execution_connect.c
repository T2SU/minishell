/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_connect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 16:19:36 by smun              #+#    #+#             */
/*   Updated: 2021/08/26 13:07:44 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <sys/wait.h>

static void	connect_pipe(int order, int fd[])
{
	if (order == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
	}
	if (order == 1)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
}

static pid_t	run_pipe(t_syntax *run, int order, int fd[])
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		connect_pipe(order, fd);
		status = execution_start(run);
		close(fd[!order]);
		exit(status);
	}
	if (pid < 0)
		exit_error();
	return (pid);
}

static int	run_logical_connection(t_connect *con)
{
	int	status;

	status = EXIT_FAILURE;
	if (con->connector == kAnd)
	{
		status = execution_start(con->first);
		if (status == EXIT_SUCCESS) // first가 성공해야만 second실행
			status = execution_start(con->second);
	}
	if (con->connector == kOr)
	{
		status = execution_start(con->first);
		if (context_is_signaled(status)) // 시그널로 종료면 그냥 리턴.
			return (status);
		if (status != EXIT_SUCCESS) // first가 실패해야만 second실행
			status = execution_start(con->second);
	}
	return (status);
}

int	execution_connect_run(t_connect *con)
{
	int		pipefd[2];
	int		status;
	pid_t	pids[2];

	if (con->connector == kPipe) // 파이프는 항상 양쪽 모두 fork해서 실행해야함.
	{
		if (-1 == pipe(pipefd))
			exit_error();
		pids[0] = run_pipe(con->first, 0, pipefd);
		pids[1] = run_pipe(con->second, 1, pipefd);
		waitpid(pids[0], &status, 0);
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(pids[1], &status, 0);
		return (status);
	}
	return (run_logical_connection(con));
}
