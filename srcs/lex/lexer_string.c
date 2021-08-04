/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 23:32:52 by smun              #+#    #+#             */
/*   Updated: 2021/08/04 17:49:03 by smun             ###   ########.fr       */
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

void	lexer_parse_string(t_lexer *lexer, t_list *list)
{
	t_strbuf	strbuf;
	char		quote;
	char		c;

	quote = lexer->str[lexer->cursor];
	lexer->cursor++;
	ft_memset(&strbuf, 0, sizeof(t_strbuf));
	while (TRUE)
	{
		c = lexer->str[lexer->cursor++];
		if (c == quote || c == '\0')
			break ;
		if (c == '\\')
			c = do_escape(lexer);
		if (!strbuf_append(&strbuf, c))
			exit_error(get_context()->executable_name, NULL, NULL);
	}
	if (!add_lex_string(kString, &strbuf, list))
		exit_error(get_context()->executable_name, NULL, NULL);
}
