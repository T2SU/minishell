/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 19:03:18 by smun              #+#    #+#             */
/*   Updated: 2021/08/19 03:23:39 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static t_syntax	*validate(t_stack *st)
{
	if (ft_lstsize(st->dat) != 1)
	{
		t_list *lst;
		lst = st->dat;
		while(lst != NULL)
		{
			t_syntax *syn = lst->content;
			printf("Type=[%d]\n",syn->type);
			syntax_print(syn);
			printf(RESET"\n------\n");
			lst = lst->next;
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
