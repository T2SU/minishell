/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bracket.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 23:32:06 by smun              #+#    #+#             */
/*   Updated: 2021/08/04 17:17:13 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_parse_bracket(t_lexer *lexer, t_list *list)
{
	const char	c = lexer->str[lexer->cursor];
	int			mode;

	if (c == '(')
		mode = kOpen;
	else
		mode = kClose;
	if (!add_lex(kParenthesis, mode, list))
		return (exit_error(get_context()->executable_name, NULL, NULL));
	lexer->cursor++;
}
