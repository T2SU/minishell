/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 14:28:18 by smun              #+#    #+#             */
/*   Updated: 2021/08/25 01:50:53 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

void	print_error(const char *str)
{
	const char	*execname = context_get()->app_name;

	if (str == NULL)
		str = strerror(context_get()->error);
	write(STDERR_FILENO, execname, ft_strlen(execname));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
}

void	exit_error(void)
{
	context_get()->error = errno;
	print_error(NULL);
	exit(EXIT_FAILURE);
}

t_bool	raise_system_error(const char *why)
{
	context_get()->error = errno;
	return (raise_error(why, strerror(context_get()->error)));
}

t_bool	raise_error(const char *why, const char *desc)
{
	const char	*execname = context_get()->app_name;

	write(STDERR_FILENO, execname, ft_strlen(execname));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, why, ft_strlen(why));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, desc, ft_strlen(desc));
	write(STDERR_FILENO, "\n", 1);
	return (FALSE);
}

t_bool	context_is_continuable(void)
{
	if (context_get()->signal)
		return (FALSE);
	if (context_get()->usererror)
		return (FALSE);
	if (context_get()->error)
		return (FALSE);
	return (TRUE);
}
