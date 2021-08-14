/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 15:12:32 by hkim              #+#    #+#             */
/*   Updated: 2020/12/26 16:29:29 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			negative;
	int			res;
	long long	tmp;

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
	while (*str >= '0' && *str <= '9')
	{
		tmp = (long long)res;
		tmp = tmp * 10 + (*str - '0');
		if (tmp * negative > 2147483647)
			return (-1);
		else if (tmp * negative < -2147483648)
			return (0);
		res = res * 10 + (*str++ - '0');
	}
	return (res * negative);
}
