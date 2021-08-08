/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_angle_bracket.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 23:32:43 by smun              #+#    #+#             */
/*   Updated: 2021/08/08 22:31:23 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_greater(t_lexer *lexer, t_list *list)
{
	if (lexer->str[lexer->cursor + 1] == '>')
	{
		lexer->cursor += 2;
		if (!add_lex(kDoubleGreater, NULL, list))
			exit_error(get_context()->executable_name, NULL, NULL);
	}
	else
	{
		lexer->cursor += 1;
		if (!add_lex(kGreater, NULL, list))
			exit_error(get_context()->executable_name, NULL, NULL);
	}
}

static void	parse_lesser(t_lexer *lexer, t_list *list)
{
	if (lexer->str[lexer->cursor + 1] == '<')
	{
		lexer->cursor += 2;
		if (!add_lex(kDoubleLesser, NULL, list))
			exit_error(get_context()->executable_name, NULL, NULL);
	}
	else
	{
		lexer->cursor += 1;
		if (!add_lex(kLesser, NULL, list))
			exit_error(get_context()->executable_name, NULL, NULL);
	}
}

void	lexer_parse_angle_bracket(t_lexer *lexer, t_list *list)
{
	const char	c = lexer->str[lexer->cursor];

	if (c == '>')
		parse_greater(lexer, list);
	if (c == '<')
		parse_lesser(lexer, list);
}
