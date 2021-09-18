/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_grammer_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 00:09:04 by smun              #+#    #+#             */
/*   Updated: 2021/09/19 01:51:27 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	peek(t_stack *stack, int index, enum e_token sttype)
{
	t_syntax	*syntax;

	syntax = stack_peek(stack, index);
	if (syntax == NULL)
		return (FALSE);
	if (sttype == kCommand)
		return (syntax_is_command(syntax));
	return (syntax->type == sttype);
}

static t_bool	match(t_stack *stack,
	enum e_token stx1, enum e_token stx2, enum e_token stx3)
{
	int	cnt;

	cnt = (stx1 != 0) + (stx2 != 0) + (stx3 != 0);
	if (stx1 != 0)
		if (!peek(stack, --cnt, stx1))
			return (FALSE);
	if (stx2 != 0)
		if (!peek(stack, --cnt, stx2))
			return (FALSE);
	if (stx3 != 0)
		if (!peek(stack, --cnt, stx3))
			return (FALSE);
	return (TRUE);
}

t_bool	syntax_reassemble(t_stack *st)
{
	if (match(st, '(', kCommand, ')'))
		syntax_make_subshell(st);
	else if (match(st, kRedir, kRedir, 0))
		syntax_make_redirections(st, stack_pop(st));
	else if (match(st, kSimpleCommand, kWord, 0))
		syntax_append_argument_to_simplecmd(st);
	else if (match(st, kConnection, kWord, 0))
		syntax_append_argument_to_connect(st);
	else if (match(st, kCommand, kRedir, 0))
		syntax_connect_redirection(st, stack_pop(st));
	else if (match(st, kRedir, kSimpleCommand, 0))
		syntax_connect_redirection_reverse(st, stack_pop(st));
	else if (match(st, kConnection, '|', kCommand))
		syntax_separate_bond_connect(st);
	else if (match(st, kCommand, '|', kCommand))
		syntax_make_connection(st, kPipe);
	else if (match(st, kCommand, kBarBar, kCommand))
		syntax_make_connection(st, kOr);
	else if (match(st, kCommand, kAndAnd, kCommand))
		syntax_make_connection(st, kAnd);
	else
		return (FALSE);
	return (TRUE);
}

t_bool	syntax_assemble(t_stack *st)
{
	if (match(st, kGreaterGreater, kWord, 0))
		syntax_make_redirection(st, kAppend);
	else if (match(st, '<', kWord, 0))
		syntax_make_redirection(st, kRead);
	else if (match(st, kLessLess, kWord, 0))
		syntax_make_redirection(st, kReadHeredoc);
	else if (match(st, '>', kWord, 0))
		syntax_make_redirection(st, kWrite);
	else if (match(st, kWord, kWordList, 0))
		syntax_make_wordlist(st, stack_pop(st));
	else if (match(st, kWord, 0, 0))
		syntax_make_wordlist(st, NULL);
	else if (match(st, kWordList, 0, 0))
		syntax_make_simplecmd(st);
	else
		return (FALSE);
	return (TRUE);
}
