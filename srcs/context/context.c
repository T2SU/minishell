/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 00:17:14 by smun              #+#    #+#             */
/*   Updated: 2021/09/12 02:53:30 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	context_init(char *argv[], char *envp[])
{
	t_context	*ctx;
	char		path[PATH_MAX];

	ctx = context_get();
	ft_bzero(ctx, sizeof(t_context));
	ctx->app_name = ft_basename(argv[0]);
	ctx->env = make_dict(envp);
	getcwd(path, PATH_MAX);
	dict_put(ctx->env, "PWD", path, 1);
	dict_del(ctx->env, "OLDPWD");
	ctx->interactive = TRUE;
}

t_context	*context_get(void)
{
	static t_context	ctx;

	return (&ctx);
}

t_bool	context_has_flag(int flag)
{
	return ((context_get()->flag & flag) != 0);
}

void	context_set_child(void)
{
	context_get()->flag |= kInChildProc;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	context_print_strsignal(int status)
{
	const int	sig = context_get_signal_num(status);

	if (!context_is_signaled(status))
		return ;
	if (sig != SIGINT)
		ft_putstr_fd(ft_strsignal(sig), STDERR_FILENO);
	printf("\n"); // 시그널로 종료되면 개행 한번..
}
