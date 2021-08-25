/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_subshell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 18:50:47 by smun              #+#    #+#             */
/*   Updated: 2021/08/25 19:12:33 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execution_subshell_run(t_subshell *subshell)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit_error();
	if (pid == 0)
		exit(execution_start(subshell->command));
	waitpid(pid, &status, 0);
	return (status);
}
