/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 23:32:52 by smun              #+#    #+#             */
/*   Updated: 2021/08/04 16:50:55 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void		free_lex_string(void *ptr)
{
	t_lex	*lex;

	lex = (t_lex *)ptr;
	free(lex->data.identifier.data);
	free(lex);
}

static t_bool	add_lex_string(t_strbuf *strbuf, t_list *list)
{
	t_lex	*lex;
	char	*str;

	str = strbuf_get(strbuf, TRUE);
	if (str == NULL)
		return (FALSE);
	lex = malloc(sizeof(t_lex));
	if (lex == NULL)
		return (FALSE);
	lex->type = kString;
	lex->data.identifier.data = str;
	list_add(list, lex, &free_lex_string);
	return (TRUE);
}

static char	do_escape(t_lexer *lexer)
{
	const char	ch = lexer->str[++lexer->cursor];

	if (ch == 'n')
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
	else if (ch == '\\')
		return ('\\');
	else if (ch == 'a')
		return ('\a');
	else if (ch == 'v')
		return ('\v');
	return (ch);
}

t_bool	lexer_parse_string(t_lexer *lexer, t_list *list)
{
	t_strbuf	strbuf;
	char		quote;
	char		c;

	quote = lexer->str[lexer->cursor];
	if (quote != '\'' && quote != '\"' && quote != '`')
		return (FALSE);
	lexer->cursor++;
	ft_memset(&strbuf, 0, sizeof(t_strbuf));
	while (TRUE)
	{
		c = lexer->str[lexer->cursor];
		if (c == quote || c == '\0')
			break ;
		if (c == '\\')
			c = do_escape(lexer);
		if (!strbuf_append(&strbuf, c))
			exit_error(get_context()->executable_name, NULL, NULL);
		lexer->cursor++;
	}
	if (c == quote)
		lexer->cursor++;
	if (!add_lex_string(&strbuf, list))
		exit_error(get_context()->executable_name, NULL, NULL);
	return (TRUE);
}
