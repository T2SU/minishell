/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 19:03:18 by smun              #+#    #+#             */
/*   Updated: 2021/08/19 00:49:59 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_syntax	*validate(t_stack *st)
{
	if (ft_lstsize(st->dat) != 1)
	{
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
		syntax_assemble(&st);
		if (lst != NULL)
			syntax_build_from_token(&st, lst->content);
		else
			return (validate(&st));
	}
}
