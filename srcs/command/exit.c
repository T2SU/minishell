/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 23:26:25 by hkim              #+#    #+#             */
/*   Updated: 2021/08/27 23:38:42 by hkim             ###   ########.fr       */
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
	printf("exit\n");
	if (argc == 1)
		exit(0);
	else if (!is_str_num(argv[1]))
	{
		printf("exit: %s: numeric argument required\n", argv[1]);
		exit(1);
	}
	else if (argc > 2)
		printf("exit: too many arguments\n");
	else
		exit(ft_atoi(argv[1]));
	return (EXIT_SUCCESS);
}
