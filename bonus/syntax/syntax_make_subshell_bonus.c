/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_make_subshell_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 23:03:48 by smun              #+#    #+#             */
/*   Updated: 2021/09/19 01:51:31 by hkim             ###   ########.fr       */
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
