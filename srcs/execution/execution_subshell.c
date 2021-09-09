/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_subshell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 18:50:47 by smun              #+#    #+#             */
/*   Updated: 2021/09/09 21:32:25 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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
		status = execution_start(subshell->command);
		if (context_is_exited(status))
			status = context_get_exit_status(status);
		else
			status |= 0200;
		exit(status);
	}
	waitpid(pid, &status, 0);
	execution_try_print_strsignal(status);
	status = retrieve_status(status);
	status &= ~(0200);
	context_get()->laststatus = status;
	return (status);
}
