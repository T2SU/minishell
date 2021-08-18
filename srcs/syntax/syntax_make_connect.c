/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_make_connect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:58:24 by smun              #+#    #+#             */
/*   Updated: 2021/08/19 03:34:11 by smun             ###   ########.fr       */
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

void	syntax_append_argument_to_connect(t_stack *st)
{
	t_list		*wordlst;
	t_word		*word;
	t_syntax	*consyntax;
	t_syntax	*cmdsyntax;

	word = syntax_strip(stack_pop(st), kWord);
	consyntax = stack_pop(st);
	cmdsyntax = consyntax->connect->second;
	wordlst = ft_lstnew(word);
	if (wordlst == NULL)
		exit_error();
	ft_lstadd_back(&cmdsyntax->simplecmd->args, wordlst);
	stack_push(st, consyntax);
}
