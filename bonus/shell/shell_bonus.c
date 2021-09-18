/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 14:20:45 by smun              #+#    #+#             */
/*   Updated: 2021/09/19 01:51:14 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <termios.h>

int	retrieve_status(int status)
{
	if (context_is_exited(status))
		status = context_get_exit_status(status);
	return (status);
}

static void	execute(t_syntax *syntax)
{
	context_get()->flag = 0;
	context_get()->interactive = FALSE;
	shell_set_termattr(TRUE);
	if (execution_prepare_heredoc(syntax))
		context_get()->laststatus = retrieve_status(execution_start(syntax));
	else
		context_get()->laststatus = EXIT_FAILURE;
	shell_set_termattr(FALSE);
	context_get()->interactive = TRUE;
	dispose_syntax(syntax);
}

void	shell_process(char *line)
{
	enum e_parsestatus	status;
	t_syntax			*syntax;

	status = parse(&syntax, line);
	if (status != kEmptyLine)
		add_history(line);
	free(line);
	if (status == kFailed)
	{
		context_get()->laststatus = context_exitcode(EXIT_FAILURE, SIGINT);
		print_error(NULL, NULL, "syntax parse error");
	}
	if (status == kSuccess)
		execute(syntax);
}

void	shell_main(void)
{
	char	*line;

	while (TRUE)
	{
		line = readline(PROMPT);
		if (line == NULL)
		{
			command_run_exit(1, NULL, NULL);
			break ;
		}
		shell_process(line);
	}
}

void	shell_set_termattr(t_bool echoctl)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	if (!echoctl)
		term.c_lflag &= ~ECHOCTL;
	else
		term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
