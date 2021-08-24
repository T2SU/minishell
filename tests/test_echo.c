/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 12:22:56 by hkim              #+#    #+#             */
/*   Updated: 2021/08/24 13:13:20 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testlib.h"
#include "testdictlib.h"
#include "functions.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

static void test_run_echo()
{
	t_list	*list;

	list = NULL;
	ft_lstadd_back(&list, ft_lstnew("abc"));
	ft_lstadd_back(&list, ft_lstnew("def"));
	run_echo(list);
	free(list->next);
	free(list);
}

static void test_run_echo_flag()
{
	t_list	*list;

	list = NULL;
	ft_lstadd_back(&list, ft_lstnew("-n"));
	ft_lstadd_back(&list, ft_lstnew("abc"));
	ft_lstadd_back(&list, ft_lstnew("def"));
	run_echo(list);
	free(list->next->next);
	free(list->next);
	free(list);
}

int		main(int argc, char *argv[])
{
	do_test_stdout(&test_run_echo,
		"abc def\n"
	);
	do_test_stdout(&test_run_echo_flag,
		"abc def"
	);
	print_test_result(argc, argv[0]);
	return (0);
}
