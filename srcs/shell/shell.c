/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 14:20:45 by smun              #+#    #+#             */
/*   Updated: 2021/08/25 14:26:23 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

t_bool	shell_is_interactive(void)
{
	if (ft_lstsize(context_get()->execution_stack.dat) > 0)
		return (FALSE);
	return (TRUE);
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
}

void	shell_clean(void)
{
}
