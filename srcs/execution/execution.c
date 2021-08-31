/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 21:22:53 by smun              #+#    #+#             */
/*   Updated: 2021/08/31 12:47:22 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dispatch(t_execution *exec)
{
	int	status;

	// 리다이렉션 설치
	execution_install_redir(exec, TRUE);
	status = EXIT_SUCCESS;
	if (exec->syntax->type == kSimpleCommand)
		status = execution_simplecmd_run(exec->syntax->simplecmd);
	else if (exec->syntax->type == kConnection)
		status = execution_connect_run(exec->syntax->connect);
	else if (exec->syntax->type == kSubShell)
		status = execution_subshell_run(exec->syntax->subshell);
	if (status >> 8) // exit 시그널이 있을 경우
		status >>= 8;
	// 리다이렉션 원복
	execution_install_redir(exec, FALSE);
	return (status);
}

// 문법 실행 메인 함수
int	execution_start(t_syntax *syntax)
{
	t_execution	exec;

	ft_bzero(&exec, sizeof(t_execution));
	exec.syntax = syntax;
	// t_syntax 구조체에 설정된 리다이렉션 준비
	if (!execution_handle_redirections(&exec))
		return (EXIT_FAILURE);
	// 실제 커맨드 실행 루틴 호출
	return (dispatch(&exec));
}
