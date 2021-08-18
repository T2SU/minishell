/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_make_simplecmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:28:10 by smun              #+#    #+#             */
/*   Updated: 2021/08/19 03:00:09 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_make_simplecmd(t_stack *st, t_syntax *redir)
{
	t_simplecmd	*simplecmd;

	simplecmd = safe_malloc(sizeof(t_simplecmd));
	ft_memset(simplecmd, 0, sizeof(t_simplecmd));
	simplecmd->args = syntax_strip(stack_pop(st), kWordList);
	if (redir != NULL)
		simplecmd->redirs = syntax_strip(redir, kRedir);
	stack_push(st, syntax_make(simplecmd, kSimpleCommand));
}

void	syntax_append_argument(t_stack *st)
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
