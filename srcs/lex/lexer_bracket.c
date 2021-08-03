/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bracket.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 23:32:06 by smun              #+#    #+#             */
/*   Updated: 2021/08/04 00:54:52 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	lexer_parse_bracket(t_lexer *lexer, t_list *list)
{
	const char	c = lexer->str[lexer->cursor];
	int			mode;

	if (c != '(' && c != ')')
		return (FALSE);
	if (c == '(')
		mode = kOpen;
	else
		mode = kClose;
	if (!add_lex(kParenthesis, mode, 0, list))
		return (FALSE);
	lexer->cursor++;
	return (TRUE);
}
