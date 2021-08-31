/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 00:17:14 by smun              #+#    #+#             */
/*   Updated: 2021/08/31 12:03:49 by smun             ###   ########.fr       */
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
