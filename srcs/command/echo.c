/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 20:50:54 by hkim              #+#    #+#             */
/*   Updated: 2021/08/27 23:07:34 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_n_option(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((i == 0 && str[i] != '-') || (i != 0 && str[i] != 'n'))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	command_run_echo(int argc, char *argv[], t_dict *dict)
{
	int	n_flag;
	int	start;
	int	i;

	(void)dict;
	n_flag = 0;
	start = 1;
	if (is_n_option(argv[1]))
	{
		n_flag = 1;
		start = 2;
	}
	i = start;
	while (i < argc)
	{
		if (i != start)
			write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
		i++;
	}
	if (!n_flag)
		write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}
