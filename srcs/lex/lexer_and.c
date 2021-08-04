/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_and.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 23:32:19 by smun              #+#    #+#             */
/*   Updated: 2021/08/04 17:31:20 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	lexer_parse_and(t_lexer *lexer, t_list *list)
{
	if (lexer->str[lexer->cursor + 1] != '&')
		return (FALSE);
	lexer->cursor += 2;
	if (!add_lex(kOperator, kAnd, list))
		exit_error(get_context()->executable_name, NULL, NULL);
	return (TRUE);
}
