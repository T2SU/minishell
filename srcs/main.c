/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 14:58:20 by smun              #+#    #+#             */
/*   Updated: 2021/08/17 17:20:12 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

int	main(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_statement	*statement;

	(void)envp;
	(void)argc;
	context_init(argv[0]);
	while (TRUE)
	{
		line = readline("PROMPT$ ");
		if (line == NULL)
			break ; // TODO: type 'exit'
		statement = parse(line);
		free(line);
		if (statement != NULL)
		{
			print_statement(statement);
			free_statement(statement);
			printf("\n");
		}
	}
	return (EXIT_SUCCESS);
}
