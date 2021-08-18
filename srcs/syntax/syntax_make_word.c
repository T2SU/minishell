/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_make_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 20:28:20 by smun              #+#    #+#             */
/*   Updated: 2021/08/18 22:26:48 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	syntax_make_wordlist(t_stack *st, t_syntax *syntax)
{
	t_list		*lst;
	t_word		*word;

	word = syntax_strip(stack_pop(st), kWord);
	lst = ft_lstnew(word);
	if (lst == NULL)
		exit_error();
	if (syntax == NULL)
		syntax = syntax_make(NULL, kWordList);
	ft_lstadd_back(&syntax->wordlist, lst);
	stack_push(st, syntax);
}
