/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 14:20:45 by smun              #+#    #+#             */
/*   Updated: 2021/08/29 14:29:13 by smun             ###   ########.fr       */
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
	context_get()->interactive = FALSE; // 시그널때문에...
	shell_set_termattr(TRUE);
	context_get()->laststatus = execution_start(syntax); // echo $?
	shell_set_termattr(FALSE);
	context_get()->interactive = TRUE;
	dispose_syntax(syntax);
}

// Ctrl+\
//   셸 프롬포트 ($)        : 셸 종료
//   명령 또는 프로그렘 실행중 : 자식 프로세스에 저 시그널을 보내서 종료시킨다. / 다시말해, 셸이 종료되는건 아니죠.
// Ctrl+C
//   셸 프롬포트 ($)        : 타이핑 하던 명령어 삭제시키고, 새로운 프롬포트
//   명령 또는 프로그램 실행중 : 자식 프로세스에 SIGINT 보내서 인터럽트 시키는거고, 다시말해서 셸이 인터럽트 되는 X.

// Ctrl+C, Ctrl+\ 부모프로세스~자식프로세스 전부다 날아가요.
// SIGINT, SIGQUIT

// minishell
//    bash
//       cat
//    hexdump
//  ps

// Ctrl+C   SIGINT 발생.

// minishell, bash, cat, hexdump, ps    ->> 전부다 SIGINT를 받아요..



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
			print_error(NULL, NULL, "syntax parse error");
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

