/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_dispose.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 13:46:05 by smun              #+#    #+#             */
/*   Updated: 2021/08/18 18:23:53 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	dispose_wordchunk(void *ptr)
{
	t_wordchunk	*wordchunk;

	wordchunk = (t_wordchunk *)ptr;
	free(wordchunk->str);
	free(wordchunk);
}

void	dispose_token(void *ptr)
{
	t_token	*token;

	token = (t_token *)ptr;
	if (token->type == Token_Word)
		ft_lstclear(&token->word.wordlist, &dispose_wordchunk);
	else
		free(token);
}
