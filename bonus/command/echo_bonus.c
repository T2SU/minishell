/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 20:50:54 by hkim              #+#    #+#             */
/*   Updated: 2021/09/19 10:28:42 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static t_bool	is_n_option(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) == 0)
		return (FALSE);
	while (str[i])
	{
		if ((i == 0 && str[i] != '-') || (i != 0 && str[i] != 'n'))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static t_bool	check_option(char **str, int *start)
{
	int		i;
	t_bool	ret;

	i = 1;
	ret = FALSE;
	while (str[i])
	{
		if (is_n_option(str[i]))
		{
			ret = TRUE;
			*start += 1;
		}
		else
			break ;
		i++;
	}
	return (ret);
}

static int	print(int i, int start, char *arg)
{
	int	printed_len;

	printed_len = 0;
	if (i != start)
	{
		write(STDOUT_FILENO, " ", 1);
		printed_len += 1;
	}
	write(STDOUT_FILENO, arg, ft_strlen(arg));
	printed_len += ft_strlen(arg);
	return (printed_len);
}

int	command_run_echo(int argc, char *argv[], t_dict *dict)
{
	int	n_flag;
	int	start;
	int	i;
	int	printed_len;

	(void)dict;
	n_flag = 0;
	start = 1;
	printed_len = 0;
	if (argc > 1 && check_option(argv, &start))
		n_flag = 1;
	i = start;
	while (i < argc)
	{
		printed_len += print(i, start, argv[i]);
		i++;
	}
	if (!n_flag)
		write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}
