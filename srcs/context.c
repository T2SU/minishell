/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 14:56:01 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 16:01:38 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_context	*get_context()
{
	static t_context	ctx;

	return (&ctx);
}

void	context_init(int argc, char *argv[], char *envp[])
{
	t_context	*ctx;

	ctx = get_context();
	ctx->executable_name = argv[0];
	ctx->prompt = ft_strdup("soone$ ");
	(void)argc;
	(void)envp;
}

void	*raise_error(const char *error, char *desc)
{
	t_context	*ctx;

	ctx = get_context();
	ctx->error = error;
	ctx->desc = desc;
	return (NULL);
}
