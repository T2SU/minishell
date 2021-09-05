/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 23:26:25 by hkim              #+#    #+#             */
/*   Updated: 2021/09/05 23:11:52 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_str_num(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			res = 0;
			break ;
		}
		i++;
	}
	return (res);
}

int	command_run_exit(int argc, char *argv[], t_dict *dict)
{
	(void)dict;
	if (!context_get()->childproc)
		write(STDERR_FILENO, "exit\n", 5);
	if (argc == 1)
		exit(0);
	else if (!is_str_num(argv[1]))
	{
		raise_arg_error(argv[0], argv[1], "numeric argument required");
		exit(1);
	}
	else if (argc <= 2)
		exit(ft_atoi(argv[1]));
	raise_error(argv[0], "too many arguments");
	return (EXIT_FAILURE);
}
