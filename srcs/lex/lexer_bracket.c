/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bracket.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 23:32:19 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 01:29:51 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_parse_bracket(t_lexer *lexer, t_list *list)
{
	if (lexer->str[lexer->cursor] == '(')
	{
		lexer->cursor += 1;
		add_lex(kOpenBracket, NULL, list);
	}
	else if (lexer->str[lexer->cursor] == ')')
	{
		lexer->cursor += 1;
		add_lex(kCloseBracket, NULL, list);
	}
}
