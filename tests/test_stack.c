/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 16:34:53 by smun              #+#    #+#             */
/*   Updated: 2021/08/18 16:51:28 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testlib.h"
#include "minishell.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

static void	test_stack_push_pop(void)
{
	t_stack		stack;

	ft_memset(&stack, 0, sizeof(t_stack));
	assert(stack_size(&stack) == 0);
	stack_push(&stack, (void*)0);
	assert(stack_size(&stack) == 1);
	stack_push(&stack, (void*)1);
	assert(stack_size(&stack) == 2);
	stack_push(&stack, (void*)2);
	assert(stack_size(&stack) == 3);
	assert(stack_pop(&stack) == (void*)2);
	assert(stack_size(&stack) == 2);
	assert(stack_pop(&stack) == (void*)1);
	assert(stack_size(&stack) == 1);
	assert(stack_pop(&stack) == (void*)0);
	assert(stack_size(&stack) == 0);
}

static void	test_stack_peek(void)
{
	t_stack		stack;

	ft_memset(&stack, 0, sizeof(t_stack));
	assert(stack_peek(&stack, 0) == NULL);
	stack_push(&stack, (void*)1);
	assert(stack_peek(&stack, 1) == NULL);
	stack_push(&stack, (void*)2);
	assert(stack_peek(&stack, 2) == NULL);
	stack_push(&stack, (void*)3);
	assert(stack_peek(&stack, -1) == NULL);
	assert(stack_peek(&stack, -3) == NULL);
	assert(stack_peek(&stack, 2147483647) == NULL);
	assert(stack_peek(&stack, -2147483648) == NULL);
	assert(stack_peek(&stack, 0) == (void*)3);
	assert(stack_peek(&stack, 1) == (void*)2);
	assert(stack_peek(&stack, 2) == (void*)1);
	assert(stack_peek(&stack, 3) == NULL);
	stack_pop(&stack);
	assert(stack_peek(&stack, 0) == (void*)2);
	assert(stack_peek(&stack, 1) == (void*)1);
	stack_pop(&stack);
	assert(stack_peek(&stack, 0) == (void*)1);
	stack_pop(&stack);
}

int		main(int argc, char *argv[])
{
	do_test(&test_stack_push_pop);
	do_test(&test_stack_peek);
	print_test_result(argc, argv[0]);
	return (0);
}
