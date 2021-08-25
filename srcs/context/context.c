/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 00:17:14 by smun              #+#    #+#             */
/*   Updated: 2021/08/25 21:11:22 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	context_init(char *argv0)
{
	ft_bzero(context_get(), sizeof(t_context));
	context_get()->app_name = ft_basename(argv0);
}

t_context	*context_get(void)
{
	static t_context	ctx;

	return (&ctx);
}

t_bool	context_is_signaled(int status)
{
	if ((status & 0177) == 0)
		return (FALSE);
	if ((status & 0177) == _WSTOPPED)
		return (FALSE);
	return (TRUE);
}
