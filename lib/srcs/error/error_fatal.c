/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_fatal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 23:34:26 by smun              #+#    #+#             */
/*   Updated: 2021/08/04 00:18:22 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

void	exit_error(char *exec, const char *error, const char *desc)
{
	const char	*errorstr = strerror(errno);

	write(STDERR_FILENO, exec, ft_strlen(exec));
	write(STDERR_FILENO, ": ", 2);
	if (error != NULL)
	{
		write(STDERR_FILENO, error, ft_strlen(error));
		write(STDERR_FILENO, desc, ft_strlen(desc));
	}
	else
		write(STDERR_FILENO, errorstr, ft_strlen(errorstr));
	exit(EXIT_FAILURE);
}
