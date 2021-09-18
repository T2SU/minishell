/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 14:58:20 by smun              #+#    #+#             */
/*   Updated: 2021/09/19 02:03:53 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

static t_bool	is_empty_elem(char *str)
{
	int	len;

	len = 0;
	while (*str)
	{
		if (!ft_strchr("\r\n\t\v\f ", *str))
			len++;
		str++;
	}
	return (len == 0);
}

static t_bool	process_c_option(int argc, char *argv[])
{
	char	**splitted;
	char	*elem;
	int		i;

	if (argc < 3)
		return (FALSE);
	if (ft_strncmp(argv[1], "-c", 3))
		return (FALSE);
	splitted = ft_split(argv[2], ';');
	if (splitted == NULL)
		exit_error();
	i = 0;
	while (TRUE)
	{
		elem = splitted[i++];
		if ((elem == NULL && i == 1) || (elem != NULL && is_empty_elem(elem)))
			exit(2);
		if (elem == NULL)
			break ;
		shell_process(ft_strdup(elem));
	}
	free_char_arrays(splitted);
	exit(context_get()->laststatus);
	return (TRUE);
}

int	main(int argc, char *argv[], char *envp[])
{
	context_init(argv, envp);
	if (process_c_option(argc, argv))
		return (EXIT_SUCCESS);
	shell_set_termattr(FALSE);
	signal(SIGQUIT, &shell_sigquit_handler);
	signal(SIGINT, &shell_sigint_handler);
	shell_main();
	return (EXIT_SUCCESS);
}
