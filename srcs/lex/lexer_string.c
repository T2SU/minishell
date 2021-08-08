/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 23:32:52 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 01:31:08 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static char	do_escape(t_lexer *lexer)
{
	const char	ch = lexer->str[lexer->cursor];

	if (ch != '\0')
		lexer->cursor++;
	if (ch == '\0' || ch == '\\')
		return ('\\');
	else if (ch == 'n')
		return ('\n');
	else if (ch == 'r')
		return ('\r');
	else if (ch == 't')
		return ('\t');
	else if (ch == 'b')
		return ('\b');
	else if (ch == '\'')
		return ('\'');
	else if (ch == '"')
		return ('"');
	else if (ch == '`')
		return ('`');
	else if (ch == '?')
		return ('?');
	else if (ch == 'v')
		return ('\v');
	return (ch);
}

static void	interpolate(t_lexer *lexer, t_list *list, t_strbuf *strbuf, char q)
{
	char	c;

	add_lex_string(kString, strbuf, list);
	add_lex(kInnerDollar, NULL, list);
	ft_memset(strbuf, 0, sizeof(t_strbuf));
	c = lexer->str[lexer->cursor];
	if (c == '\0' || c == q)
		return ;
	while (ft_isalnum(c) || c == '_')
	{
		if (!strbuf_append(strbuf, c))
			exit_error(get_context()->executable_name, NULL, NULL);
		c = lexer->str[++lexer->cursor];
	}
	add_lex_string(kIdentifier, strbuf, list);
	ft_memset(strbuf, 0, sizeof(t_strbuf));
}

static void	parse_character(t_lexer *lexer, t_strbuf *strbuf, char c)
{
	if (c == '\\')
		c = do_escape(lexer);
	if (!strbuf_append(strbuf, c))
		exit_error(get_context()->executable_name, NULL, NULL);
}

void	lexer_parse_string(t_lexer *lexer, t_list *list)
{
	t_strbuf	strbuf;
	char		quote;
	char		c;

	quote = lexer->str[lexer->cursor++];
	ft_memset(&strbuf, 0, sizeof(t_strbuf));
	while (TRUE)
	{
		c = lexer->str[lexer->cursor];
		if (c != '\0')
			lexer->cursor++;
		if (c == quote || c == '\0')
			break ;
		if (c == '$')
			interpolate(lexer, list, &strbuf, quote);
		else
			parse_character(lexer, &strbuf, c);
	}
	if (strbuf_length(&strbuf) == 0)
		if (!strbuf_append(&strbuf, quote))
			exit_error(get_context()->executable_name, NULL, NULL);
	add_lex_string(kString, &strbuf, list);
}
