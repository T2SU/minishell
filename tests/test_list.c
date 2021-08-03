/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 14:15:47 by smun              #+#    #+#             */
/*   Updated: 2021/08/03 16:31:16 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testlib.h"
#include "minishell.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

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

static void	test_list_get_sequence(void)
{
	t_list	list;
	long	i;

	ft_memset(&list, 0, sizeof(t_list));
	i = 0;
	while (i < 10)
	{
		list_add(&list, (void*)i, NULL);
		i++;	
	}
	assert(list.length == 10);
	assert(list_get(&list, 0) != NULL);
	assert(list_get(&list, 0)->data == (void*)0);
	assert(list_get(&list, 1) != NULL);
	assert(list_get(&list, 1)->data == (void*)1);
	assert(list_get(&list, 2) != NULL);
	assert(list_get(&list, 2)->data == (void*)2);
	assert(list_get(&list, 3) != NULL);
	assert(list_get(&list, 3)->data == (void*)3);
	assert(list_get(&list, 4) != NULL);
	assert(list_get(&list, 4)->data == (void*)4);
	assert(list_get(&list, 5) != NULL);
	assert(list_get(&list, 5)->data == (void*)5);
	assert(list_get(&list, 6) != NULL);
	assert(list_get(&list, 6)->data == (void*)6);
	assert(list_get(&list, 7) != NULL);
	assert(list_get(&list, 7)->data == (void*)7);
	assert(list_get(&list, 8) != NULL);
	assert(list_get(&list, 8)->data == (void*)8);
	assert(list_get(&list, 9) != NULL);
	assert(list_get(&list, 9)->data == (void*)9);
	list_free(&list);
}

static void	test_list_get_random(void)
{
	t_list	list;
	long	i;

	ft_memset(&list, 0, sizeof(t_list));
	i = 0;
	while (i < 1000)
	{
		list_add(&list, (void*)i, NULL);
		i++;	
	}
	assert(list.length == 1000);
	assert(list_get(&list, 0) != NULL);
	assert(list_get(&list, 0)->data == (void*)0);
	assert(list_get(&list, 137) != NULL);
	assert(list_get(&list, 137)->data == (void*)137);
	assert(list_get(&list, 499) != NULL);
	assert(list_get(&list, 499)->data == (void*)499);
	assert(list_get(&list, 500) != NULL);
	assert(list_get(&list, 500)->data == (void*)500);
	assert(list_get(&list, 501) != NULL);
	assert(list_get(&list, 501)->data == (void*)501);
	assert(list_get(&list, 674) != NULL);
	assert(list_get(&list, 674)->data == (void*)674);
	assert(list_get(&list, 236) != NULL);
	assert(list_get(&list, 236)->data == (void*)236);
	assert(list_get(&list, 796) != NULL);
	assert(list_get(&list, 796)->data == (void*)796);
	assert(list_get(&list, 999) != NULL);
	assert(list_get(&list, 999)->data == (void*)999);
	list_free(&list);
}

static void	test_list_get_failed(void)
{
	t_list	list;
	long	i;

	ft_memset(&list, 0, sizeof(t_list));
	i = 0;
	while (i < 1000)
	{
		list_add(&list, (void*)i, NULL);
		i++;	
	}
	assert(list.length == 1000);
	assert(list_get(&list, -1) == NULL);
	assert(list_get(&list, -10) == NULL);
	assert(list_get(&list, 1000) == NULL);
	assert(list_get(&list, 1001) == NULL);
	list_free(&list);
}

static void	test_list_remove_one(void)
{
	t_list	list;

	ft_memset(&list, 0, sizeof(t_list));
	list_add(&list, (void*)1, NULL);
	list_add(&list, (void*)2, NULL);
	list_add(&list, (void*)3, NULL);
	list_add(&list, (void*)4, NULL);
	list_add(&list, (void*)5, NULL);
	list_add(&list, (void*)6, NULL);
	list_add(&list, (void*)7, NULL);
	assert(list.length == 7);
	assert(list_remove(&list, 0) == 1);
	assert(list.length == 6);
	assert(list.head->prev == NULL);
	assert(list.head->data == (void*)2);
	assert(list_remove(&list, 1) == 1);
	assert(list.length == 5);
	assert(list.head->next->prev == list.head);
	assert(list.head->next->data == (void*)4);
	assert(list_remove(&list, 5) == 0);
	list_free(&list);
}

static void	test_list_remove_tail(void)
{
	t_list	list;

	ft_memset(&list, 0, sizeof(t_list));
	list_add(&list, (void*)1, NULL);
	list_add(&list, (void*)2, NULL);
	list_add(&list, (void*)3, NULL);
	list_add(&list, (void*)4, NULL);
	list_add(&list, (void*)5, NULL);
	list_add(&list, (void*)6, NULL);
	list_add(&list, (void*)7, NULL);
	assert(list.length == 7);
	assert(list_remove(&list, 6) == 1);
	assert(list.length == 6);
	assert(list.tail->next == NULL);
	assert(list.tail->data == (void*)6);
	assert(list.tail->prev->next == list.tail);
	assert(list_remove(&list, 4) == 1);
	assert(list.length == 5);
	assert(list.tail->prev->next == list.tail);
	assert(list.tail->prev->data == (void*)4);
	list_free(&list);
}

static void	test_list_remove_if_some(void)
{
	t_list	list;

	ft_memset(&list, 0, sizeof(t_list));
	list_add(&list, (void*)1, NULL);
	list_add(&list, (void*)2, NULL);
	list_add(&list, (void*)1, NULL);
	list_add(&list, (void*)4, NULL);
	list_add(&list, (void*)2, NULL);
	assert(list.length == 5);
	assert(list_get(&list, 0)->data == (void*)1);
	assert(list_get(&list, 1)->data == (void*)2);
	assert(list_get(&list, 2)->data == (void*)1);
	assert(list_get(&list, 3)->data == (void*)4);
	assert(list_get(&list, 4)->data == (void*)2);
	assert(list_remove_if(&list, (void*)1) == 2);
	assert(list.length == 3);
	assert(list_get(&list, 0)->data == (void*)2);
	assert(list_get(&list, 1)->data == (void*)4);
	assert(list_get(&list, 2)->data == (void*)2);
	assert(list_remove_if(&list, (void*)2) == 2);
	assert(list.length == 1);
	assert(list_get(&list, 0)->data == (void*)4);
	assert(list_get(&list, 0)->prev == NULL);
	assert(list_get(&list, 0)->next == NULL);
	assert(list_remove_if(&list, (void*)4) == 1);
	assert(list.length == 0);
	assert(list.head == NULL);
	assert(list.tail == NULL);
	list_free(&list);
}

static void	test_list_remove_with_destructor(void)
{
	t_list		list;
	const char	*temp;
	const char	*strings[] = {
		"Hello World",
		"42 Seoul | minishell",
		"I got you!",
		"Doremi Pio Leo Siya Kyou Zia"
	};
	char		*allocated_strings[4];

	ft_memset(&list, 0, sizeof(t_list));
	temp = strings[0];
	allocated_strings[0] = strcpy(malloc(strlen(temp) + 1), temp);
	assert(!strcmp(temp, list_add(&list, allocated_strings[0], &free)->data));
	temp = strings[1];
	allocated_strings[1] = strcpy(malloc(strlen(temp) + 1), temp);
	assert(!strcmp(temp, list_add(&list, allocated_strings[1], &free)->data));
	temp = strings[2];
	allocated_strings[2] = strcpy(malloc(strlen(temp) + 1), temp);
	assert(!strcmp(temp, list_add(&list, allocated_strings[2], &free)->data));
	temp = strings[3];
	allocated_strings[3] = strcpy(malloc(strlen(temp) + 1), temp);
	assert(!strcmp(temp, list_add(&list, allocated_strings[3], &free)->data));
	
	assert(list.length == 4); // 0, 1, 2, 3
	
	assert(list_remove_if(&list, allocated_strings[3]) == 1);
	assert(list.length == 3); // 0, 1, 2
	assert(!strcmp(strings[2], list_get(&list, 2)->data));
	
	assert(list_remove(&list, 0) == 1);
	assert(list.length == 2); // 1, 2
	assert(!strcmp(strings[2], list_get(&list, 1)->data));
	
	assert(list_remove_if(&list, allocated_strings[2]) == 1);
	assert(list.length == 1); // 1
	assert(!strcmp(strings[1], list_get(&list, 0)->data));

	assert(list_remove(&list, 1) == 0);
	assert(list_remove(&list, 0) == 1);
	assert(list.length == 0);

	list_free(&list);
}

int		main(int argc, char *argv[])
{
	do_test(&test_list_add_one);
	do_test(&test_list_add_twice);
	do_test(&test_list_add_triple);
	do_test(&test_list_free);
	do_test(&test_list_get_sequence);
	do_test(&test_list_get_random);
	do_test(&test_list_get_failed);
	do_test(&test_list_remove_one);
	do_test(&test_list_remove_tail);
	do_test(&test_list_remove_if_some);
	do_test(&test_list_remove_with_destructor);
	print_test_result(argc, argv[0]);
	
	system("leaks test_list.out");
	return (0);
}
