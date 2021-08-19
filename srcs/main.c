/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 14:58:20 by smun              #+#    #+#             */
/*   Updated: 2021/08/19 15:20:59 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_syntax	*syntax;

	(void)envp;
	(void)argc;
	context_init(argv[0]);
	while (TRUE)
	{
		line = readline("PROMPT$ ");
		if (line == NULL)
			break ; // TODO: type 'exit'
		syntax = parse(line);
		dispose_syntax(syntax);
		free(line);
	}
	return (EXIT_SUCCESS);
}
