/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 23:32:31 by smun              #+#    #+#             */
/*   Updated: 2021/08/08 22:32:06 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_parse_bar(t_lexer *lexer, t_list *list)
{
	if (lexer->str[lexer->cursor + 1] == '|')
	{
		lexer->cursor += 2;
		if (!add_lex(kDoubleBar, NULL, list))
			exit_error(get_context()->executable_name, NULL, NULL);
	}
	else
	{
		lexer->cursor += 1;
		if (!add_lex(kBar, NULL, list))
			exit_error(get_context()->executable_name, NULL, NULL);
	}
}
