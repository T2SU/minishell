/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 14:58:20 by smun              #+#    #+#             */
/*   Updated: 2021/08/25 15:58:07 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <termios.h>

static void	set_term(void)
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int	main(int argc, char *argv[], char *envp[])
{
	(void)envp;
	(void)argc;
	context_init(argv[0]);
	set_term();
	signal(SIGQUIT, &shell_sigquit_handler);
	signal(SIGINT, &shell_sigint_handler);
	shell_main();
	return (EXIT_SUCCESS);
}
