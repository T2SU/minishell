/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsignal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 23:42:07 by smun              #+#    #+#             */
/*   Updated: 2021/09/06 01:04:03 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_signalstr_darwin2(char *messages[])
{
	messages[SIGXCPU] = "Cputime limit exceeded";
	messages[SIGXFSZ] = "Filesize limit exceeded";
	messages[SIGVTALRM] = "Virtual timer expired";
	messages[SIGPROF] = "Profiling timer expired";
	messages[SIGWINCH] = "Window size changes";
	messages[SIGINFO] = "Information request";
	messages[SIGUSR1] = "User defined signal 1";
	messages[SIGUSR2] = "User defined signal 2";
}

static void	init_signalstr_darwin(char *messages[])
{
	messages[0] = "Unknown signal";
	messages[SIGHUP] = "Hangup";
	messages[SIGINT] = "Interrupt";
	messages[SIGQUIT] = "Quit";
	messages[SIGILL] = "Illegal instruction";
	messages[SIGTRAP] = "Trace/BPT trap";
	messages[SIGABRT] = "Abort trap";
	messages[SIGEMT] = "EMT trap";
	messages[SIGFPE] = "Floating point exception";
	messages[SIGKILL] = "Killed";
	messages[SIGBUS] = "Bus error";
	messages[SIGSEGV] = "Segmentation fault";
	messages[SIGSYS] = "Bad system call";
	messages[SIGPIPE] = "Broken pipe";
	messages[SIGALRM] = "Alarm clock";
	messages[SIGTERM] = "Terminated";
	messages[SIGURG] = "Urgent I/O condition";
	messages[SIGSTOP] = "Suspended (signal)";
	messages[SIGTSTP] = "Suspended";
	messages[SIGCONT] = "Continued";
	messages[SIGCHLD] = "Child exited";
	messages[SIGTTIN] = "Stopped (tty input)";
	messages[SIGTTOU] = "Stopped (tty output)";
	messages[SIGIO] = "I/O possible";
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

	if (!messages[0])
		init_strsignal(messages);
	ft_bzero(ret, sizeof(ret));
	if (signal < 1 || signal >= 32 || messages[signal] == NULL)
		signal = 0;
	ft_strlcpy(ret, messages[signal], sizeof(ret));
	temp = ft_itoa(signal);
	if (temp == NULL)
		exit_error();
	ft_strlcat(ret, ": ", sizeof(ret));
	ft_strlcat(ret, temp, sizeof(ret));
	free(temp);
	return (ret);
}
