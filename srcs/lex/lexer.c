/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 18:21:29 by smun              #+#    #+#             */
/*   Updated: 2021/08/04 00:55:05 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

t_bool	add_lex(int type, int data, int data2, t_list *list)
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
	{
		lex->data.out.mode = data;
		lex->data.out.fd = data2;
	}
	if (!list_add(list, lex, &free))
		return (FALSE);
	return (TRUE);
}

static t_bool	parse_string(const char *command, char quote, t_list *list)
{
	
}

t_bool	parse_lex(const char *command, t_list *list)
{
	t_lexer	lexer;

	lexer.str = command;
	lexer.state = kLexerNormal;
	lexer.cursor = 0;
	while (lexer.str[lexer.cursor] != '\0')
	{
		
		
	}
	return (0);
}
