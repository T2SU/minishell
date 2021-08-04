/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 18:21:29 by smun              #+#    #+#             */
/*   Updated: 2021/08/04 17:50:37 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

t_bool	add_lex(int type, int data, t_list *list)
{
	t_lex	*lex;

	lex = malloc(sizeof(t_lex));
	if (lex == NULL)
		return (FALSE);
	lex->type = type;
	if (type == kParenthesis)
		lex->data.parenthesis.data = data;
	else if (type == kOperator)
		lex->data.op.type = data;
	else if (type == kInRedirection)
		lex->data.in.mode = data;
	else if (type == kOutRedirection)
		lex->data.out.mode = data;
	if (!list_add(list, lex, &free))
		return (FALSE);
	return (TRUE);
}

static void		free_lex_string(void *ptr)
{
	t_lex	*lex;

	lex = (t_lex *)ptr;
	free(lex->data.identifier.data);
	free(lex);
}

t_bool	add_lex_string(int type, t_strbuf *strbuf, t_list *list)
{
	t_lex	*lex;
	char	*str;

	str = strbuf_get(strbuf, TRUE);
	if (str == NULL)
		return (FALSE);
	lex = malloc(sizeof(t_lex));
	if (lex == NULL)
		return (FALSE);
	lex->type = type;
	lex->data.identifier.data = str;
	list_add(list, lex, &free_lex_string);
	return (TRUE);
}

static t_bool	try_parse_lex(t_lexer *lexer, t_list *list)
{
	char	ch;

	ch = lexer->str[lexer->cursor];
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
	else
		return (FALSE);
	return (TRUE);
}

void	parse_lex(const char *command, t_list *list)
{
	t_lexer		lexer;
	t_strbuf	strbuf;
	char		ch;

	ft_memset(&strbuf, 0, sizeof(t_strbuf));
	ft_memset(&lexer, 0, sizeof(t_lexer));
	lexer.str = command;
	while (TRUE)
	{
		ch = lexer.str[lexer.cursor];
		if (ch == '\0')
			break ;
		if (try_parse_lex(&lexer, list))
			lexer_lush_identifier(&strbuf, list);
		else
			lexer_build_identifier(&strbuf, ch);
		lexer.cursor++;
	}
}
