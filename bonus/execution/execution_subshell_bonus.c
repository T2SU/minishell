/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_subshell_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 18:50:47 by smun              #+#    #+#             */
/*   Updated: 2021/09/19 10:29:51 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int	execution_subshell_run(t_subshell *subshell)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit_error();
	if (pid == 0)
	{
		context_get()->flag |= kInSubShell;
		context_set_child();
		status = context_delisig_execution(subshell->command);
		exit(status);
	}
	waitpid(pid, &status, 0);
	context_delisig_process(&status);
	context_get()->laststatus = status;
	return (status);
}
