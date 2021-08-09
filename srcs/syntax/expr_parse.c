/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:46:37 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 23:53:47 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_parsers(t_expr*(**funcs)(t_parser *))
{
	funcs[Expression_Command] = &parse_command;
}

static t_expr	*call_parser(t_parser *parser, int type)
{
	static	t_expr*(*funcs[Expression_Command])(t_parser *);

	if (!funcs)
		init_parsers(funcs);
	if (funcs[type] == NULL)
		return (NULL);
	return ((funcs[type])(parser));
}

t_expr		*get_expr(t_parser *parser, int type)
{
	t_expr	*expr;

	expr = call_parser(parser, type);
	if (expr == NULL)
		return (NULL);
	if (expr->type != type)
	{
		expr_free(expr);
		return (NULL);
	}
	return (expr);
}
