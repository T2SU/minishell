/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_error_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 14:28:18 by smun              #+#    #+#             */
/*   Updated: 2021/09/19 10:29:04 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

void	exit_error(void)
{
	context_get()->error = errno;
	print_error(NULL, NULL, NULL);
	exit(EXIT_FAILURE);
}

t_bool	raise_system_error(const char *why)
{
	context_get()->error = errno;
	return (raise_error(why, strerror(context_get()->error)));
}

t_bool	raise_error(const char *why, const char *desc)
{
	return (print_error(context_get()->app_name, why, desc));
}

t_bool	print_error(const char *app, const char *why, const char *desc)
{
	if (app == NULL)
		app = context_get()->app_name;
	write(STDERR_FILENO, app, ft_strlen(app));
	write(STDERR_FILENO, ": ", 2);
	if (why != NULL)
	{
		write(STDERR_FILENO, why, ft_strlen(why));
		write(STDERR_FILENO, ": ", 2);
	}
	if (desc == NULL)
		desc = strerror(context_get()->error);
	write(STDERR_FILENO, desc, ft_strlen(desc));
	write(STDERR_FILENO, "\n", 1);
	return (FALSE);
}
