/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 14:17:51 by smun              #+#    #+#             */
/*   Updated: 2021/08/25 15:59:32 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	shell_sigint_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	if (context_get()->heredoc)
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
	if (shell_is_interactive())
	{
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}
