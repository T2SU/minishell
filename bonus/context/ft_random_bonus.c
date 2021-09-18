/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 01:26:48 by smun              #+#    #+#             */
/*   Updated: 2021/09/19 01:50:21 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>

static t_bool	make_readable(char *buffer, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (buffer[i] == -128)
			buffer[i] = '-';
		else if (buffer[i] < 0)
			buffer[i] = ((-buffer[i]) % ('z' - 'a')) + 'a';
		else
			buffer[i] = ((buffer[i]) % ('Z' - 'A')) + 'A';
		i++;
	}
	return (TRUE);
}

t_bool	ft_randomstr(char *buffer, size_t len)
{
	int		fd;
	size_t	i;
	ssize_t	readsz;

	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (FALSE);
	i = 0;
	while (i < len)
	{
		readsz = read(fd, &buffer[i], len - i);
		if (readsz <= 0)
			break ;
		i += readsz;
	}
	close(fd);
	if (readsz < 0)
		return (FALSE);
	return (make_readable(buffer, len));
}
