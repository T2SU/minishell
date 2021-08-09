/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_fatal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 23:34:26 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 21:25:23 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

void	exit_error(char *exec)
{
	const char	*errorstr = strerror(errno);

	write(STDERR_FILENO, exec, ft_strlen(exec));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, errorstr, ft_strlen(errorstr));
	exit(EXIT_FAILURE);
}
