/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_error2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 18:13:17 by hkim              #+#    #+#             */
/*   Updated: 2021/09/19 01:50:18 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	raise_system_arg_error(const char *why, const char *arg)
{
	context_get()->error = errno;
	return (raise_arg_error(why, arg, strerror(context_get()->error)));
}

t_bool	raise_arg_error(const char *why, const char *arg, const char *desc)
{
	return (print_arg_error(context_get()->app_name, why, arg, desc));
}

t_bool	print_arg_err_quote(const char *app, const char *why, const char *arg,
						const char *desc)
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
	if (arg != NULL)
	{
		write(STDERR_FILENO, "`", 1);
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, "'", 1);
		write(STDERR_FILENO, ": ", 2);
	}
	if (desc == NULL)
		desc = strerror(context_get()->error);
	write(STDERR_FILENO, desc, ft_strlen(desc));
	write(STDERR_FILENO, "\n", 1);
	return (FALSE);
}

t_bool	raise_arg_err_quote(const char *why, const char *arg, const char *desc)
{
	return (print_arg_err_quote(context_get()->app_name, why, arg, desc));
}

t_bool	print_arg_error(const char *app, const char *why, const char *arg,
						const char *desc)
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
	if (arg != NULL)
	{
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, ": ", 2);
	}
	if (desc == NULL)
		desc = strerror(context_get()->error);
	write(STDERR_FILENO, desc, ft_strlen(desc));
	write(STDERR_FILENO, "\n", 1);
	return (FALSE);
}
