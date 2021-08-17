/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parser_statement.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 13:54:14 by smun              #+#    #+#             */
/*   Updated: 2021/08/17 19:06:15 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_statement	*single_job_statement(t_parser *parser)
{
	t_statement	*ret;
	t_job		*job;

	job = next_job(parser);
	if (job == NULL)
		return (NULL);
	ret = malloc(sizeof(t_statement));
	if (ret == NULL)
		exit_error();
	ft_memset(ret, 0, sizeof(t_statement));
	ret->type = StatementType_SingleJob;
	ret->job = job;
	return (ret);
}

static int	get_statement_type(t_parser *parser)
{
	int	ret;

	ret = StatementType_Normal;
	skip_whitespaces(parser);
	if (is_acceptable(parser->cur, Token_And))
		ret = StatementType_And;
	if (is_acceptable(parser->cur, Token_Or))
		ret = StatementType_Or;
	if (ret != StatementType_Normal)
		parser->cur = parser->cur->next;
	return (ret);
}

static t_statement	*parse_statement(t_parser *parser, int order)
{
	t_statement		*ret;

	if (order == 1)
	{
		if (is_acceptable(parser->cur, Token_OpenBracket))
		{
			(parser->scope)++;
			parser->cur = parser->cur->next;
			ret = next_statement(parser);
		}
		else
			ret = single_job_statement(parser);
	}
	else
		ret = next_statement(parser);
	return (ret);
}

t_statement	*make_statement(t_statement *ref)
{
	t_statement	*ret;

	ret = malloc(sizeof(t_statement));
	if (ret == NULL)
		exit_error();
	ft_memcpy(ret, ref, sizeof(t_statement));
	return (ret);
}

t_statement	*next_statement(t_parser *parser)
{
	t_statement	ret;

	skip_whitespaces(parser);
	ft_memset(&ret, 0, sizeof(t_statement));
	ret.first = parse_statement(parser, 1);
	if (ret.first == NULL)
		return (NULL);
	if (is_acceptable(parser->cur, Token_CloseBracket))
	{
		if (--(parser->scope) < 0)
			return (free_statement(ret.first));
		parser->cur = parser->cur->next;
		return (make_statement(&ret));
	}
	ret.type = get_statement_type(parser);
	if (ret.type != StatementType_Normal)
	{
		ret.second = parse_statement(parser, 2);
		if (ret.second == NULL)
			return (free_statement(ret.first));
	}
	return (make_statement(&ret));
}
