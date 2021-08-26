/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 14:17:51 by smun              #+#    #+#             */
/*   Updated: 2021/08/26 13:06:41 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

void	shell_sigint_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	if (context_get()->heredoc) // heredoc을 읽는 중일땐 부모 프로세스에서 시그널을 받아선 안됨
		return ;
	if (!context_get()->interactive) // 명령을 처리중일땐 부모 프로세스에서 시그널을 받아선 안됨
		return ;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	shell_sigquit_handler(int sig)
{
	if (sig != SIGQUIT)
		return ;
	if (context_get()->interactive) // 프롬포트 상태에서 SIGQUIT를 받으면 이 코드로 시그널을 무시시킴.
	{
		rl_on_new_line();
		rl_redisplay();
	}
}
