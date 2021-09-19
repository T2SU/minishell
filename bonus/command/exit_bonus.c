/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 23:26:25 by hkim              #+#    #+#             */
/*   Updated: 2021/09/19 10:28:47 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	is_str_num(const char *str)
{
	int	i;
	int	len;
	int	res;

	i = 0;
	len = ft_strlen(str) - 1;
	res = 1;
	while (len >= 0 && (ft_strchr(" \t\r\f", str[len])))
		len--;
	while (str[i] && ft_strchr(" \t\r\f", str[i]))
		i++;
	if (len < 0)
		res = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (i < len)
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

static int	do_convert(const char *str, long long *pres, int *pnegative)
{
	unsigned long long	tmp;
	long long			res;

	res = *pres;
	while (*str >= '0' && *str <= '9')
	{
		tmp = (unsigned long long)res;
		tmp = tmp * 10 + (*str - '0');
		if (tmp > 9223372036854775807 && *pnegative == 1)
			return (-1);
		else if (tmp > 9223372036854775808ULL && *pnegative == -1)
			return (0);
		res = res * 10 + (*str++ - '0');
	}
	*pres = res;
	return (1);
}

long long	ft_atol(const char *str)
{
	int			negative;
	long long	res;
	int			status;

	res = 0;
	negative = 1;
	while (*str == ' ' || *str == '\f' || *str == '\n'
		|| *str == '\r' || *str == '\t' || *str == '\v')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			negative = -1;
	}
	while (*str == '0')
		str++;
	status = do_convert(str, &res, &negative);
	if (status != 1)
		return (status);
	return (res * negative);
}

static t_bool	is_long_long(const char *str)
{
	int			negative;
	long long	res;

	res = 0;
	negative = 1;
	while (*str == ' ' || *str == '\f' || *str == '\n'
		|| *str == '\r' || *str == '\t' || *str == '\v')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			negative = -1;
	}
	while (*str == '0')
		str++;
	if (ft_strlen(str) >= 20)
		return (FALSE);
	if (do_convert(str, &res, &negative) != 1)
		return (FALSE);
	return (TRUE);
}

int	command_run_exit(int argc, char *argv[], t_dict *dict)
{
	(void)dict;
	if (!context_has_flag(kInChildProc))
		write(STDERR_FILENO, "exit\n", 5);
	if (argc == 1)
		exit(0);
	else if (!is_str_num(argv[1]) || !is_long_long(argv[1]))
	{
		raise_arg_error(argv[0], argv[1], "numeric argument required");
		exit(255);
	}
	else if (argc <= 2)
		exit((int)ft_atol(argv[1]));
	raise_error(argv[0], "too many arguments");
	return (EXIT_FAILURE);
}
