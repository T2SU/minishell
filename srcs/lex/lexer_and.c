/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_and.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 23:32:19 by smun              #+#    #+#             */
/*   Updated: 2021/08/08 22:29:49 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_parse_and(t_lexer *lexer, t_list *list)
{
	if (lexer->str[lexer->cursor + 1] == '&')
	{
		lexer->cursor += 2;
		if (!add_lex(kDoubleAmpersand, NULL, list))
			exit_error(get_context()->executable_name, NULL, NULL);
	}
	else
	{
		lexer->cursor += 1;
		if (!add_lex(kAmpersand, NULL, list))
			exit_error(get_context()->executable_name, NULL, NULL);
	}
}
