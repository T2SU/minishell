/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_wait_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 00:17:14 by smun              #+#    #+#             */
/*   Updated: 2021/09/19 01:50:19 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*
** WTERMSIG(status).
*/

int	context_get_signal_num(int status)
{
	return ((status & 0177));
}

/*
** W_EXITCODE(code, sig)
*/

int	context_exitcode(int code, int sig)
{
	return ((code << 8) | sig);
}
