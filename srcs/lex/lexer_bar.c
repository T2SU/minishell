/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 23:32:31 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 14:42:05 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_parse_bar(t_lexer *lexer, t_list *list)
{
	if (lexer->str[lexer->cursor + 1] == '|')
	{
		lexer->cursor += 2;
		add_lex(Lex_DoubleBar, NULL, list);
	}
	else
	{
		lexer->cursor += 1;
		add_lex(Lex_Bar, NULL, list);
	}
}
