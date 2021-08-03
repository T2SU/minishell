/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 14:15:47 by smun              #+#    #+#             */
/*   Updated: 2021/08/03 14:40:31 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testlib.h"
#include "minishell.h"
#include <assert.h>

static void	test_list_add_one(void)
{
	t_list	list;

	ft_memset(&list, 0, sizeof(t_list));
	assert(list_add(&list, (void*)1, NULL) != NULL);
	assert(list.head != NULL);
	assert(list.tail != NULL);
	assert(list.head->data == (void*)1);
	assert(list.tail->data == (void*)1);
	assert(list.head->next == NULL);
	assert(list.tail->prev == NULL);
	assert(list.length == 1);
}

static void	test_list_add_twice(void)
{
	t_list	list;

	ft_memset(&list, 0, sizeof(t_list));
	assert(list_add(&list, (void*)1, NULL) != NULL);
	assert(list_add(&list, (void*)2, NULL) != NULL);
	assert(list.head != NULL);
	assert(list.tail != NULL);
	assert(list.head->data == (void*)1);
	assert(list.tail->data == (void*)2);
	assert(list.head->next == list.tail);
	assert(list.tail->prev == list.head);
	assert(list.head->next->next == NULL);
	assert(list.tail->prev->prev == NULL);
	assert(list.length == 2);
}

static void	test_list_add_triple(void)
{
	t_list	list;

	ft_memset(&list, 0, sizeof(t_list));
	assert(list_add(&list, (void*)1, NULL) != NULL);
	assert(list_add(&list, (void*)2, NULL) != NULL);
	assert(list_add(&list, (void*)3, NULL) != NULL);
	assert(list.head != NULL);
	assert(list.tail != NULL);
	assert(list.head->data == (void*)1);
	assert(list.head->next->data == (void*)2);
	assert(list.head->next->next->data == (void*)3);
	assert(list.tail->data == (void*)3);
	assert(list.tail->prev->data == (void*)2);
	assert(list.tail->prev->prev->data == (void*)1);
	assert(list.head->next->next->next == NULL);
	assert(list.tail->prev->prev->prev == NULL);
	assert(list.length == 3);
}

static void	test_list_free(void)
{
	t_list	list;

	ft_memset(&list, 0, sizeof(t_list));
	assert(list_add(&list, (void*)1, NULL) != NULL);
	assert(list_add(&list, (void*)2, NULL) != NULL);
	assert(list_add(&list, (void*)3, NULL) != NULL);
	list_free(&list);
}

int		main(int argc, char *argv[])
{
	do_test(&test_list_add_one);
	do_test(&test_list_add_twice);
	do_test(&test_list_add_triple);
	do_test(&test_list_free);
	print_test_result(argc, argv[0]);
	return (0);
}
