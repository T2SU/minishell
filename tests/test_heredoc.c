/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 14:41:16 by smun              #+#    #+#             */
/*   Updated: 2021/08/25 14:46:16 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testlib.h"
#include "minishell.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <readline/readline.h>

static void test_heredoc(void)
{
	t_redir redir;
	redir.heredoc_eof = "EOF";

	signal(SIGINT, &shell_sigint_handler);
	while (TRUE)
	{
		char *line = readline(PROMPT);
		if (line == NULL)
			break;
		if (!strcmp(line, "heredoc"))
		{
			char *filename = execution_make_heredoc(&redir);
			printf("filename = %s\n", filename);
			free(filename);
		}
		free(line);
	}
}

int main(void)
{
	test_heredoc();
	return 0;
}
