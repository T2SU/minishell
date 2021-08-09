/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_and.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 23:32:19 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 14:41:45 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_parse_and(t_lexer *lexer, t_list *list)
{
	if (lexer->str[lexer->cursor + 1] == '&')
	{
		lexer->cursor += 2;
		add_lex(Lex_DoubleAmpersand, NULL, list);
	}
	else
	{
		lexer->cursor += 1;
		add_lex(Lex_Ampersand, NULL, list);
	}
}
