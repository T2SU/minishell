/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 19:03:18 by smun              #+#    #+#             */
/*   Updated: 2021/08/19 16:19:32 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static t_syntax	*validate(t_stack *st)
{
	t_syntax	*syn;
	t_list		*lst;

	if (ft_lstsize(st->dat) != 1)
	{
		if (VERBOSE)
		{
			printf(YELLOW"[[Remaining tokens in stack]]\n"RESET);
			lst = st->dat;
			while (lst != NULL)
			{
				syn = lst->content;
				printf("Type=[%d]\n", syn->type);
				syntax_print(syn);
				printf(RESET"\n------\n");
				lst = lst->next;
			}
		}
		ft_lstclear(&st->dat, &dispose_syntax);
		return (NULL);
	}
	return (stack_pop(st));
}

t_syntax	*syntax_parse(t_list *tokens)
{
	t_stack	st;
	t_list	*lst;

	ft_memset(&st, 0, sizeof(t_stack));
	lst = tokens;
	while (TRUE)
	{
		if (!syntax_reassemble(&st) && !syntax_assemble(&st))
		{
			if (lst == NULL)
				break ;
			syntax_build_from_token(&st, lst->content);
			lst = lst->next;
		}
	}
	return (validate(&st));
}

int	parse(t_syntax **syntax, char *line)
{
	t_tokenizer	tokenizer;
	t_list		*tokens;

	tokenizer.str = line;
	tokenizer.quote = 0;
	tokens = tokenize(&tokenizer);
	if (tokens == NULL)
		return (kEmptyLine);
	if (VERBOSE)
		print_tokens(tokens);
	*syntax = syntax_parse(tokens);
	ft_lstclear(&tokens, dispose_token);
	if (*syntax != NULL && VERBOSE)
	{
		syntax_print(*syntax);
		printf(RESET"\n");
	}
	if (*syntax == NULL)
		return (kFailed);
	return (kSuccess);
}
