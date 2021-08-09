/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 15:08:12 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 16:06:35 by smun             ###   ########.fr       */
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
	while (parser->current != NULL)
	{
		lex = parser->current->data;
		if (lex->type != Lex_Identifier && lex->type != Lex_String)
			break ;
		if (lex->type != Lex_Splitter)
			flush_argument(parser, &strbuf);
		else
		{
			if (!strbuf_appends(&strbuf, lex->data))
				exit_error(get_context()->executable_name, NULL, NULL);
		}
		parser->current = parser->current->next;
	}
	add_argument(parser, &strbuf);
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
	while (parser->current != NULL)
	{
		parser->current = parser->current->next;
	}
}
