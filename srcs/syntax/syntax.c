/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 20:31:25 by smun              #+#    #+#             */
/*   Updated: 2021/08/19 01:02:20 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_syntax	*syntax_make(void *data, enum e_token desired_type)
{
	t_syntax	*ret;

	ret = safe_malloc(sizeof(t_syntax));
	ft_memset(ret, 0, sizeof(t_syntax));
	ret->type = desired_type;
	if (desired_type == kWord)
		ret->word = data;
	else if (desired_type == kWordList)
		ret->wordlist = data;
	else if (desired_type == kSimpleCommand)
		ret->simplecmd = data;
	else if (desired_type == kRedir)
		ret->redirs = data;
	else if (desired_type == kSubShell)
		ret->subshell = data;
	else if (desired_type == kConnection)
		ret->connect = data;
	return (ret);
}

void	*syntax_strip(t_syntax *syntax, enum e_token desired_type)
{
	void	*ret;

	ret = NULL;
	if (desired_type == kWord)
		ret = syntax->word;
	else if (desired_type == kWordList)
		ret = syntax->wordlist;
	else if (desired_type == kRedir)
		ret = syntax->redirs;
	else if (desired_type == kSubShell)
		ret = syntax->subshell;
	else if (desired_type == kConnection)
		ret = syntax->connect;
	else if (desired_type == kSimpleCommand)
		ret = syntax->simplecmd;
	free(syntax);
	return (ret);
}

t_bool	syntax_is_command(t_syntax *syntax)
{
	if (syntax->type == kConnection)
		return (TRUE);
	if (syntax->type == kSubShell)
		return (TRUE);
	if (syntax->type == kSimpleCommand)
		return (TRUE);
	if (syntax->type == kRedir)
		return (TRUE);
	return (FALSE);
}

void	syntax_build_from_token(t_stack *st, t_token *token)
{
	void		*data;

	data = NULL;
	if (token->type == kWord)
		data = token->word;
	stack_push(st, syntax_make(data, token->type));
}
