/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 15:08:12 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 16:11:50 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void	flush_argument(t_parser *parser, t_strbuf *strbuf)
{
	if (strbuf_length(strbuf) == 0)
		return ;
	if (!list_add(&parser->collected_args, strbuf_get(&strbuf, TRUE), &free))
		exit_error(get_context()->executable_name, NULL, NULL);
}

void	syntax_append_argument(t_parser *parser)
{
	t_strbuf	strbuf;
	t_lex		*lex;
	t_list		*collected_args;

	collected_args = &parser->collected_args;
	ft_memset(collected_args, 0, sizeof(t_list));
	ft_memset(&strbuf, 0, sizeof(t_strbuf));
	lex = parser->current->data;
	if (lex->type != Lex_Splitter)
		flush_argument(parser, &strbuf);
	else
	{
		if (!strbuf_appends(&strbuf, lex->data))
			exit_error(get_context()->executable_name, NULL, NULL);
	}
}

t_syntax	*syntax_build_command(t_parser *parser)
{
	t_syntax	*syntax;

	if (parser->collected_args.length == 0)
		return (NULL);
	syntax = malloc(sizeof(t_syntax));
	if (syntax == NULL)
		exit_error(get_context()->executable_name, NULL, NULL);
	syntax->type = Syntax_Command;
	syntax->data.command.list = parser->collected_args;
	return (syntax);
}

t_syntax	*syntax_parse(t_parser *parser)
{
	t_lex		*lex;
	t_syntax	*syntax;

	while (parser->current != NULL)
	{
		lex = parser->current->data;
		if (lex->type == Lex_Bar)
			syntax = syntax_parse_pipe(parser);
		if (lex->type == Lex_DoubleBar)
			syntax = syntax_parse_or(parser);
		else if (lex->type == Lex_DoubleBar)
			syntax = syntax_parse_or(parser);
		else if (lex->type == Lex_Lesser)
			syntax = syntax_parse_read(parser);
		else if (lex->type == Lex_DoubleLesser)
			syntax = syntax_parse_readdelim(parser);
		else if (lex->type == Lex_Greater)
			syntax = syntax_parse_write(parser);
		else if (lex->type == Lex_DoubleGreater)
			syntax = syntax_parse_append(parser);
		else if (lex->type == Lex_OpenBracket)
			syntax = syntax_parse_subshell(parser);
		else if (lex->type == Lex_DoubleAmpersand)
			syntax = syntax_parse_and(parser);
		else
			syntax = raise_error("Unexpected token");
		parser->current = parser->current->next;
	}
}
