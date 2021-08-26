/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 18:16:33 by smun              #+#    #+#             */
/*   Updated: 2021/08/26 13:23:36 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testlib.h"
#include "minishell.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <readline/readline.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void sighandler(int sig)
{
	if (sig != SIGINT)
		return ;
	printf("SIGINT(%d) from %d\n", sig, getpid());
}

int main(void)
{
	int status;

	signal(SIGINT, &sighandler);
	signal(SIGQUIT, &sighandler);
	pid_t pid = fork();
	if (pid == 0)
	{
		pid_t pid2 = fork();
		if (pid2 == 0)
		{
			pid_t sub = fork();
			if (sub == 0)
			{
				char *argv[] = {"/bin/cat", NULL};
				char *envp[] = {NULL};
				execve(argv[0], argv, envp);
			}
			waitpid(sub, &status, 0);
			if (status != 0)
				exit(EXIT_FAILURE);
			exit(EXIT_SUCCESS);
		}
		waitpid(pid2, &status, 0);
		if (status != 0)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
	printf("exit = %d\n", status);
}
