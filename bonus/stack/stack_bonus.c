/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 16:23:09 by smun              #+#    #+#             */
/*   Updated: 2021/09/19 01:51:18 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	*stack_peek(t_stack *stack, int index)
{
	t_list	*lst;

	lst = stack->dat;
	while (lst != NULL && index-- > 0)
		lst = lst->next;
	if (index != -1 || lst == NULL)
		return (NULL);
	return (lst->content);
}

void	stack_push(t_stack *stack, void *data)
{
	t_list	*lst;

	lst = ft_lstnew(data);
	if (lst == NULL)
		exit_error();
	ft_lstadd_front(&stack->dat, lst);
}

void	*stack_pop(t_stack *stack)
{
	t_list	lst;

	if (stack->dat == NULL)
		return (NULL);
	lst = *stack->dat;
	free(stack->dat);
	stack->dat = lst.next;
	return (lst.content);
}

int	stack_size(t_stack *stack)
{
	int		len;
	t_list	*lst;

	len = 0;
	lst = stack->dat;
	while (lst != NULL)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}
