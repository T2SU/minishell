/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_make_word_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 20:28:20 by smun              #+#    #+#             */
/*   Updated: 2021/09/19 01:51:32 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	syntax_make_wordlist(t_stack *st, t_syntax *syntax)
{
	t_list		*wordlst;
	t_word		*word;

	word = syntax_strip(stack_pop(st), kWord);
	wordlst = ft_lstnew(word);
	if (wordlst == NULL)
		exit_error();
	if (syntax == NULL)
		syntax = syntax_make(NULL, kWordList);
	ft_lstadd_back(&syntax->wordlist, wordlst);
	stack_push(st, syntax);
}
