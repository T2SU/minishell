/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 21:22:53 by smun              #+#    #+#             */
/*   Updated: 2021/09/12 17:28:24 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dispatch(t_execution *exec)
{
	int	status;

	execution_install_redir(exec, TRUE);
	status = context_exitcode(EXIT_SUCCESS, 0);
	if (exec->syntax->type == kSimpleCommand)
		status = execution_simplecmd_run(exec->syntax->simplecmd);
	else if (exec->syntax->type == kConnection)
		status = execution_connect_run(exec->syntax->connect);
	else if (exec->syntax->type == kSubShell)
		status = execution_subshell_run(exec->syntax->subshell);
	execution_install_redir(exec, FALSE);
	return (status);
}

int	execution_start(t_syntax *syntax)
{
	t_execution	exec;

	ft_bzero(&exec, sizeof(t_execution));
	exec.syntax = syntax;
	if (!execution_handle_redirections(&exec))
		return (EXIT_FAILURE);
	return (dispatch(&exec));
}
