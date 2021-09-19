/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 14:17:51 by smun              #+#    #+#             */
/*   Updated: 2021/09/19 10:29:59 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

void	shell_sigint_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	if (context_get()->heredoc)
		return ;
	if (!context_get()->interactive)
		return ;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	shell_sigquit_handler(int sig)
{
	if (sig != SIGQUIT)
		return ;
	if (context_get()->interactive)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}
