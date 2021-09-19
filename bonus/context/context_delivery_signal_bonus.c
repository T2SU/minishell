/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_delivery_signal_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 21:57:13 by smun              #+#    #+#             */
/*   Updated: 2021/09/19 10:29:01 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	context_delisig_execution(t_syntax *syntax)
{
	int	status;

	status = execution_start(syntax);
	if (context_is_exited(status))
		status = context_get_exit_status(status);
	else
		status |= 0200;
	return (status);
}

static void	try_print_strsignal(int status)
{
	if (context_has_flag(kInChildProc))
		return ;
	if (context_is_signaled(status))
	{
		context_print_strsignal(status);
		return ;
	}
	status = retrieve_status(status);
	if ((status & 0200) != 0)
		context_print_strsignal(context_get_signal_num(status));
}

int	context_delisig_process(int *pstatus)
{
	try_print_strsignal(*pstatus);
	*pstatus = retrieve_status(*pstatus);
	*pstatus &= ~(0200);
	return (*pstatus);
}
