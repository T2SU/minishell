/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 14:58:20 by smun              #+#    #+#             */
/*   Updated: 2021/08/19 19:38:00 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char *argv[], char *envp[])
{
	enum e_parsestatus	status;
	char				*line;
	t_syntax			*syntax;

	(void)envp;
	(void)argc;
	context_init(argv[0]);
	while (TRUE)
	{
		line = readline("PROMPT$ ");
		if (line == NULL)
			break ;
		status = parse(&syntax, line);
		if (status != kEmptyLine)
			add_history(line);
		free(line);
		if (status == kFailed)
			print_error("syntax parse error");
		if (status == kSuccess)
			dispose_syntax(syntax);
	}
	return (EXIT_SUCCESS);
}
