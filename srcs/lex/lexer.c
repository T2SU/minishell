/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 18:21:29 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 00:33:29 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static t_bool	is_lexable(char ch)
{
	if (ch == '&')
		return (TRUE);
	else if (ch == '|')
		return (TRUE);
	else if (ch == '<' || ch == '>')
		return (TRUE);
	else if (ch == '(' || ch == ')')
		return (TRUE);
	else if (ch == '\'' || ch == '"' || ch == '`')
		return (TRUE);
	else if (ch == ' ' || ch == '\t')
		return (TRUE);
	else if (ch == '$')
		return (TRUE);
	return (FALSE);
}

static t_bool	try_parse_lex(t_lexer *lexer, t_list *list, t_strbuf *strbuf)
{
	char	ch;

	ch = lexer->str[lexer->cursor];
	if (!is_lexable(ch))
		return (FALSE);
	lexer_flush_identifier(strbuf, list);
	if (ch == '&')
		lexer_parse_and(lexer, list);
	else if (ch == '|')
		lexer_parse_bar(lexer, list);
	else if (ch == '<' || ch == '>')
		lexer_parse_angle_bracket(lexer, list);
	else if (ch == '(' || ch == ')')
		lexer_parse_bracket(lexer, list);
	else if (ch == '\'' || ch == '"' || ch == '`')
		lexer_parse_string(lexer, list);
	else if (ch == ' ' || ch == '\t')
		lexer_parse_splitter(lexer, list);
	else if (ch == '$')
		lexer_parse_variable(lexer, list);
	return (TRUE);
}

void	parse_lex(const char *command, t_list *list)
{
	t_lexer		lexer;
	t_strbuf	strbuf;

	ft_memset(&strbuf, 0, sizeof(t_strbuf));
	ft_memset(&lexer, 0, sizeof(t_lexer));
	lexer.str = command;
	while (TRUE)
	{
		if (lexer.str[lexer.cursor] == '\0')
			break ;
		if (!try_parse_lex(&lexer, list, &strbuf))
			lexer_build_identifier(&strbuf, lexer.str[lexer.cursor++]);
	}
	lexer_flush_identifier(&strbuf, list);
}
