/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bracket.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 23:32:19 by smun              #+#    #+#             */
/*   Updated: 2021/08/08 22:34:33 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_parse_bracket(t_lexer *lexer, t_list *list)
{
	if (lexer->str[lexer->cursor] == '(')
	{
		lexer->cursor += 1;
		if (!add_lex(kOpenBracket, NULL, list))
			exit_error(get_context()->executable_name, NULL, NULL);
	}
	else if (lexer->str[lexer->cursor] == ')')
	{
		lexer->cursor += 1;
		if (!add_lex(kCloseBracket, NULL, list))
			exit_error(get_context()->executable_name, NULL, NULL);
	}
}
