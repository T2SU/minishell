/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr_parse_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 15:46:41 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 23:44:10 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_string_or_splitter(int type)
{
	if (type == Lex_String)
		return (TRUE);
	if (type == Lex_Identifier)
		return (TRUE);
	if (type == Lex_Splitter)
		return (TRUE);
	if (type == Lex_InnerDollar)
		return (TRUE);
	if (type == Lex_OuterDollar)
		return (TRUE);
	return (FALSE);
}

static void	append_token(t_strbuf *strbuf, t_list *list, t_elem *elem)
{
	t_lex		*lex;

	lex = elem->data;
	if (!strbuf_appends(strbuf, lex->data))
		exit_error(get_context()->executable_name);
	list_remove_if(list, elem);
}

static t_syntax	*clean_by_fail(t_list *collected, t_strbuf *strbuf)
{
	list_free(collected);
	list_free(&strbuf->list);
	return (NULL);
}

t_expr	*parse_command(t_parser *parser)
{
	t_elem		*cur;
	t_elem		*next;
	t_lex		*lex;

	cur = parser->current;
	while (cur != NULL)
	{
		lex = cur->data;
		next = cur->next;
		if (!is_string_or_splitter(lex->type))
			break ;
		if (lex->type != Lex_String && lex->type != Lex_Identifier)
			collect_token(&parser->collected, &parser->strbuf);
		if (lex->type == Lex_InnerDollar || lex->type == Lex_OuterDollar)
			if (!parse_variable(&parser->collected, parser->lexes, cur))
				return (clean_by_fail(&parser->collected, &parser->strbuf));
		if (lex->type == Lex_String || lex->type == Lex_Identifier)
			append_token(&parser->strbuf, parser->lexes, cur);
		cur = next;
	}
	parser->current = cur;
}
