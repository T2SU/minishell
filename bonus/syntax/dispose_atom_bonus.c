/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose_atom_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 13:46:05 by smun              #+#    #+#             */
/*   Updated: 2021/09/19 01:51:23 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	dispose_wordchunk(void *ptr)
{
	t_wordchunk	*wordchunk;

	if (ptr == NULL)
		return ;
	wordchunk = (t_wordchunk *)ptr;
	free(wordchunk->str);
	free(wordchunk);
}

void	dispose_token(void *ptr)
{
	t_token	*token;

	if (ptr == NULL)
		return ;
	token = (t_token *)ptr;
	if (token->type == kWord)
		dispose_word(token->word);
	free(token);
}

void	dispose_word(void *ptr)
{
	t_word	*word;

	if (ptr == NULL)
		return ;
	word = (t_word *)ptr;
	ft_lstclear(&word->wordlist, &dispose_wordchunk);
	free(word);
}
