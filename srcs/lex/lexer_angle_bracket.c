/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_angle_bracket.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 23:32:43 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 14:40:41 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_greater(t_lexer *lexer, t_list *list)
{
	if (lexer->str[lexer->cursor + 1] == '>')
	{
		lexer->cursor += 2;
		add_lex(Lex_DoubleGreater, NULL, list);
	}
	else
	{
		lexer->cursor += 1;
		add_lex(Lex_Greater, NULL, list);
	}
}

static void	parse_lesser(t_lexer *lexer, t_list *list)
{
	if (lexer->str[lexer->cursor + 1] == '<')
	{
		lexer->cursor += 2;
		add_lex(Lex_DoubleLesser, NULL, list);
	}
	else
	{
		lexer->cursor += 1;
		add_lex(Lex_Lesser, NULL, list);
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
