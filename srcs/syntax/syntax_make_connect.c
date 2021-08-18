/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_make_connect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:58:24 by smun              #+#    #+#             */
/*   Updated: 2021/08/18 23:03:10 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_make_connection(t_stack *st, int type)
{
	t_connect	*con;

	con = safe_malloc(sizeof(t_connect));
	con->second = stack_pop(st);
	(void)stack_pop(st);
	con->first = stack_pop(st);
	con->connector = type;
	stack_push(st, syntax_make(con, kConnection));
}
