/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_make_subshell.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 23:03:48 by smun              #+#    #+#             */
/*   Updated: 2021/08/19 15:52:04 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_make_subshell(t_stack *st)
{
	t_subshell	*subshell;

	subshell = safe_malloc(sizeof(t_subshell));
	free(stack_pop(st));
	subshell->command = stack_pop(st);
	free(stack_pop(st));
	stack_push(st, syntax_make(subshell, kSubShell));
}
