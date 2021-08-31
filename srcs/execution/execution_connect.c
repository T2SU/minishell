/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_connect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 16:19:36 by smun              #+#    #+#             */
/*   Updated: 2021/08/31 15:34:53 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <sys/wait.h>

// fd[0] -> READ    fd[1] -> WRITE
static void	connect_pipe(int order, int fd[])
{
	if (order == 0) // 왼쪽
	{
		close(fd[0]); // 왼쪽은 읽을 필요가 없으니.. READ용 fd는 close.
		dup2(fd[1], STDOUT_FILENO); // 왼쪽 친구가 STDOUT으로 출력하는걸 파이프의 WRITE용 fd로 설정.
	}
	if (order == 1) // 오른쪽
	{
		close(fd[1]); // 오른쪽에 있는 친구는 읽기만 하지, 쓰기를 할 일이 없으니.. WRITE용 fd는 close.
		dup2(fd[0], STDIN_FILENO); // 오른쪽 친구가 STDIN으로 입력받는걸(read) 파이프의 READ용 fd로 설정.
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
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(pids[0], &status, 0);
		waitpid(pids[1], &status, 0);
		return (status);
	}
	return (run_logical_connection(con));
}
