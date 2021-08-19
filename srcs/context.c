/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 00:17:14 by smun              #+#    #+#             */
/*   Updated: 2021/08/19 21:25:07 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

void	context_init(char *argv0)
{
	context_get()->app_name = ft_basename(argv0);
}

t_context	*context_get(void)
{
	static t_context	ctx;

	return (&ctx);
}

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
