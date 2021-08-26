/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 14:58:20 by smun              #+#    #+#             */
/*   Updated: 2021/08/26 21:35:33 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <signal.h>

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	context_init(argv, envp);
	shell_set_termattr(FALSE);
	signal(SIGQUIT, &shell_sigquit_handler);
	signal(SIGINT, &shell_sigint_handler);
	shell_main();
	return (EXIT_SUCCESS);
}
