/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 14:20:45 by smun              #+#    #+#             */
/*   Updated: 2021/08/25 21:03:00 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <termios.h>

static void	execute(t_syntax *syntax)
{
	context_get()->interactive = FALSE;
	shell_set_termattr(TRUE);
	context_get()->laststatus = execution_start(syntax);
	shell_set_termattr(FALSE);
	context_get()->interactive = TRUE;
	dispose_syntax(syntax);
}

void	shell_main(void)
{
	enum e_parsestatus	status;
	char				*line;
	t_syntax			*syntax;

	while (TRUE)
	{
		line = readline(PROMPT);
		if (line == NULL)
			break ; // TODO  call exit
		status = parse(&syntax, line);
		if (status != kEmptyLine)
			add_history(line);
		free(line);
		if (status == kFailed)
			print_error("syntax parse error");
		if (status == kSuccess)
			execute(syntax);
	}
}

void	shell_set_termattr(t_bool echoctl)
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	if (!echoctl)
		term.c_lflag &= ~ECHOCTL;
	else
		term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

