/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_make_simplecmd_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:28:10 by smun              #+#    #+#             */
/*   Updated: 2021/09/19 10:27:34 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	syntax_make_simplecmd(t_stack *st)
{
	t_simplecmd	*simplecmd;

	simplecmd = safe_malloc(sizeof(t_simplecmd));
	ft_memset(simplecmd, 0, sizeof(t_simplecmd));
	simplecmd->args = syntax_strip(stack_pop(st), kWordList);
	stack_push(st, syntax_make(simplecmd, kSimpleCommand));
}

void	syntax_append_argument_to_simplecmd(t_stack *st)
{
	t_list		*wordlst;
	t_word		*word;
	t_syntax	*cmdsyntax;

	word = syntax_strip(stack_pop(st), kWord);
	cmdsyntax = stack_pop(st);
	wordlst = ft_lstnew(word);
	if (wordlst == NULL)
		exit_error();
	ft_lstadd_back(&cmdsyntax->simplecmd->args, wordlst);
	stack_push(st, cmdsyntax);
}
