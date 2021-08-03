/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 23:32:31 by smun              #+#    #+#             */
/*   Updated: 2021/08/04 00:54:45 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	lexer_parse_bar(t_lexer *lexer, t_list *list)
{
	const char	c = lexer->str[lexer->cursor];
	int			mode;

	if (c != '|')
		return (FALSE);
	lexer->cursor++;
	if (lexer->str[lexer->cursor + 1] == '|')
	{
		lexer->cursor++;
		if (!add_lex(kOperator, kOr, 0, list))
			exit_error(get_context()->executable_name, NULL, NULL);
	}
	else
	{
		if (!add_lex(kPipe, 0, 0, list))
			exit_error(get_context()->executable_name, NULL, NULL);
	}
	return (TRUE);
}
