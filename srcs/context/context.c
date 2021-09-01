/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 00:17:14 by smun              #+#    #+#             */
/*   Updated: 2021/09/01 14:13:47 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	context_init(char *argv[], char *envp[])
{
	t_context	*ctx;

	ctx = context_get();
	ft_bzero(ctx, sizeof(t_context));
	ctx->app_name = ft_basename(argv[0]);
	ctx->env = make_dict(envp);
	ctx->interactive = TRUE;
}

t_context	*context_get(void)
{
	static t_context	ctx;

	return (&ctx);
}

/*
** WIFSIGNALED(status).
**
** Attention to different MACRO definiton in Linux(GNU) system beside macOS.
** While 'Norm' restricts the use of this macro,
** We have to expose the contents of the bitwise operation.
*/

t_bool	context_is_signaled(int status)
{
	return (status != 0177 && (status & 0177) != 0);
}

/*
** WIFEXITED(status).
*/

t_bool	context_is_exited(int status)
{
	return ((status & 0177) == 0);
}

/*
** WEXITSTATUS(status).
*/

t_bool	context_get_exit_status(int status)
{
	return ((status >> 8) & 0xff);
}
