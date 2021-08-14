/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 02:13:51 by hkim              #+#    #+#             */
/*   Updated: 2020/12/28 17:41:05 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char			c;
	unsigned int	i;

	if (n < 0)
	{
		n = n * -1;
		write(fd, "-", 1);
	}
	i = (unsigned int)n;
	if (i <= 9)
	{
		c = i + '0';
		write(fd, &c, 1);
	}
	else
	{
		ft_putnbr_fd(i / 10, fd);
		c = i % 10 + '0';
		write(fd, &c, 1);
	}
}
