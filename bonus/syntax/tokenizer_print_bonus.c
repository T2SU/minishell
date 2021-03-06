/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_print_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 14:54:36 by smun              #+#    #+#             */
/*   Updated: 2021/09/19 10:27:52 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include <stdio.h>

static void	print_word(t_list *lst)
{
	t_wordchunk	*wc;

	wc = lst->content;
	if (wc->flag != WordFlag_None)
		printf(" {$%s}", wc->str);
	else
		printf(" {%s}", wc->str);
	if (wc->quote)
		printf(" [Q:%c]", wc->quote);
	printf("\n");
	lst = lst->next;
}

static void	print_word_first(t_list *lst, int type)
{
	if (lst == NULL)
		printf("[%02d] ", type);
	else
		printf("[%02d] ", type);
	print_word(lst);
}

void	print_tokens(t_list *tokens)
{
	t_list		*t;
	t_token		*token;
	t_list		*lst;

	t = tokens;
	while (t != NULL)
	{
		token = t->content;
		if (token->type == kWord)
		{
			lst = token->word->wordlist;
			print_word_first(lst, token->type);
			lst = lst->next;
			while (lst != NULL)
			{
				printf("     ");
				print_word(lst);
				lst = lst->next;
			}
		}
		else
			printf("[%02d] %s\n", token->type, token->chars);
		t = t->next;
	}
	printf("\n");
}
