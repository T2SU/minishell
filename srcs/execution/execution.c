/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 21:22:53 by smun              #+#    #+#             */
/*   Updated: 2021/08/25 14:59:47 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	execution_start(t_syntax *syntax)
{
	t_execution	exec;

	ft_bzero(&exec, sizeof(t_execution));
	exec.syntax = syntax;
	if (!execution_handle_redirections(&exec))
		return (FALSE);
	return (TRUE);
}
