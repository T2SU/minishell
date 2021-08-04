/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_angle_bracket.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 23:32:43 by smun              #+#    #+#             */
/*   Updated: 2021/08/04 17:16:35 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_out_redirection(t_lexer *lexer, t_list *list)
{
	lexer->cursor++;
	if (lexer->str[lexer->cursor] == '>')
	{
		lexer->cursor++;
		if (!add_lex(kOutRedirection, kAppend, list))
			exit_error(get_context()->executable_name, NULL, NULL);
	}
	else
	{
		if (!add_lex(kOutRedirection, kWrite, list))
			exit_error(get_context()->executable_name, NULL, NULL);
	}
}

static void	parse_in_redirection(t_lexer *lexer, t_list *list)
{
	lexer->cursor++;
	if (lexer->str[lexer->cursor + 1] == '<')
	{
		lexer->cursor++;
		if (!add_lex(kInRedirection, kReadTillDelim, list))
			exit_error(get_context()->executable_name, NULL, NULL);
	}
	else
	{
		if (!add_lex(kInRedirection, kRead, list))
			exit_error(get_context()->executable_name, NULL, NULL);
	}
}

void	lexer_parse_angle_bracket(t_lexer *lexer, t_list *list)
{
	const char	c = lexer->str[lexer->cursor];

	if (c == '>')
		parse_out_redirection(lexer, list);
	if (c == '<')
		parse_in_redirection(lexer, list);
}
