/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr_build.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:25:35 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 23:44:05 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

t_expr	*build_expr_command(t_parser *parser)
{
	t_expr	*expr;

	collect_token(&parser->collected, &parser->strbuf);
	expr = malloc(sizeof(t_expr));
	if (expr == NULL || parser->collected.length == 0)
	{
		list_free(&parser->strbuf.list);
		list_free(&parser->collected);
		return (NULL);
	}
	expr->type = Expression_Command;
	expr->data.command.list = parser->collected;
	ft_memset(&parser->collected, 0, sizeof(t_list));
	ft_memset(&parser->strbuf, 0, sizeof(t_strbuf));
	return (expr);
}
