/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_connect_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 16:19:36 by smun              #+#    #+#             */
/*   Updated: 2021/09/19 10:29:29 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
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
		if (order == 1)
			context_get()->laststatus = 0;
		context_set_child();
		connect_pipe(order, fd);
		status = context_delisig_execution(run);
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

	status = context_exitcode(EXIT_FAILURE, 0);
	if (con->connector == kAnd)
	{
		status = execution_start(con->first);
		if (context_is_exited(status) && context_get_exit_status(status) == 0)
			status = execution_start(con->second);
	}
	if (con->connector == kOr)
	{
		status = execution_start(con->first);
		context_get()->laststatus = retrieve_status(status);
		if (context_has_flag(kThrowed))
			return (status);
		if (!context_is_exited(status) || context_get_exit_status(status) != 0)
			status = execution_start(con->second);
	}
	context_get()->laststatus = retrieve_status(status);
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
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(pids[0], &status, 0);
		waitpid(pids[1], &status, 0);
		context_delisig_process(&status);
		return (status);
	}
	return (run_logical_connection(con));
}
