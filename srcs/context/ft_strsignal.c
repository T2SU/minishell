/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsignal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 23:42:07 by smun              #+#    #+#             */
/*   Updated: 2021/09/06 01:34:14 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_signalstr_darwin2(char *messages[])
{
	messages[24] = "Cputime limit exceeded";
	messages[25] = "Filesize limit exceeded";
	messages[26] = "Virtual timer expired";
	messages[27] = "Profiling timer expired";
	messages[28] = "Window size changes";
	messages[29] = "Information request";
	messages[30] = "User defined signal 1";
	messages[31] = "User defined signal 2";
}

static void	init_signalstr_darwin(char *messages[])
{
	messages[0] = "Unknown signal";
	messages[1] = "Hangup";
	messages[2] = "Interrupt";
	messages[3] = "Quit";
	messages[4] = "Illegal instruction";
	messages[5] = "Trace/BPT trap";
	messages[6] = "Abort trap";
	messages[7] = "EMT trap";
	messages[8] = "Floating point exception";
	messages[9] = "Killed";
	messages[10] = "Bus error";
	messages[11] = "Segmentation fault";
	messages[12] = "Bad system call";
	messages[13] = "Broken pipe";
	messages[14] = "Alarm clock";
	messages[15] = "Terminated";
	messages[16] = "Urgent I/O condition";
	messages[17] = "Suspended (signal)";
	messages[18] = "Suspended";
	messages[19] = "Continued";
	messages[20] = "Child exited";
	messages[21] = "Stopped (tty input)";
	messages[22] = "Stopped (tty output)";
	messages[23] = "I/O possible";
	init_signalstr_darwin2(messages);
}

static void	init_strsignal(char *messages[])
{
	if (__APPLE__)
	{
		init_signalstr_darwin(messages);
		init_signalstr_darwin2(messages);
	}
	else
	{
		messages[0] = "Unknown signal "
			"(ft_strsignal is only supported in Darwin)";
	}
}

char	*ft_strsignal(int signal)
{
	static char	*messages[32];
	static char	ret[1024];
	char		*temp;
	int			strindex;

	if (!messages[0])
		init_strsignal(messages);
	ft_bzero(ret, sizeof(ret));
	strindex = signal;
	if (signal < 1 || signal >= 32 || messages[signal] == NULL)
		strindex = 0;
	ft_strlcpy(ret, messages[strindex], sizeof(ret));
	temp = ft_itoa(signal);
	if (temp == NULL)
		exit_error();
	ft_strlcat(ret, ": ", sizeof(ret));
	ft_strlcat(ret, temp, sizeof(ret));
	free(temp);
	return (ret);
}
