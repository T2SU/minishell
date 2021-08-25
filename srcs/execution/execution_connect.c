/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_connect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 16:19:36 by smun              #+#    #+#             */
/*   Updated: 2021/08/25 20:04:38 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

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

int	run_logical_connection(t_connect *con)
{
	int	status;

	status = EXIT_FAILURE;
	if (con->connector == kAnd)
	{
		status = execution_start(con->first);
		if (status == EXIT_SUCCESS)
			status = execution_start(con->second);
	}
	if (con->connector == kOr)
	{
		status = execution_start(con->first);
		if (status != EXIT_SUCCESS)
			status = execution_start(con->second);
	}
	return (status);
}

int	execution_connect_run(t_connect *con)
{
	int		pipefd[2];
	int		status;
	pid_t	pids[2];

	if (con->connector == kPipe)
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
