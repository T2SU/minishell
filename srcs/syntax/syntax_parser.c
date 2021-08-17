/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 22:52:02 by smun              #+#    #+#             */
/*   Updated: 2021/08/17 17:19:43 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	skip_whitespaces(t_parser *parser)
{
	t_token		*token;

	while (parser->cur != NULL)
	{
		token = parser->cur->content;
		if (token->type != Token_WhiteSpace)
			break ;
		parser->cur = parser->cur->next;
	}
}

t_bool	is_acceptable(t_list *lst, int type)
{
	t_token		*token;

	if (lst == NULL)
		return (FALSE);
	token = (t_token *)lst->content;
	return (token->type == type);
}

static void	print_syntax_error(t_parser *parser)
{
	char		errmsg[260];
	t_token		*token;

	ft_memset(errmsg, 0, sizeof(errmsg));
	ft_strlcat(errmsg, "syntax error near `", sizeof(errmsg));
	if (parser->cur == NULL)
		ft_strlcat(errmsg, "EOF", sizeof(errmsg));
	else
	{
		token = (t_token *)parser->cur->content;
		ft_strlcat(errmsg, token->data, sizeof(errmsg));
	}
	ft_strlcat(errmsg, "`", sizeof(errmsg));
	print_error(errmsg);
}

t_statement	*parse(const char *command)
{
	t_parser	parser;
	t_tokenizer	tokenizer;
	t_statement	*statement;

	tokenizer.str = command;
	tokenizer.quote = 0;
	parser.lst = tokenize(&tokenizer);
	parser.scope = 0;
	parser.cur = parser.lst;
	skip_whitespaces(&parser);
	statement = NULL;
	if (parser.cur != NULL)
	{
		statement = next_statement(&parser);
		if (statement == NULL)
			print_syntax_error(&parser);
	}
	ft_lstclear(&parser.lst, &free);
	return (statement);
}
