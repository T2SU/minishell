/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_dict.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 23:14:30 by smun              #+#    #+#             */
/*   Updated: 2021/08/22 18:27:10 by hkim             ###   ########.fr       */
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

static void	test_makedict_simple(void)
{
	t_dict	*dict;

	dict = make_dict(
		(char*[])
		{
			"USER=minishell",
			"VERSION=1.1",
			NULL
		}
	);
	assert(assert_dictpair(dict,
		2,
			"USER", "minishell",
			"VERSION", "1.1"
	));
	dict_free(dict);
	assert(assert_leaks());
}

static void	test_makedict_specialcases1(void)
{
	t_dict	*dict;

	dict = make_dict(
		(char*[])
		{
			"USER=minishell=GO=",
			"=helloworld",
			"VERSION=",
			"=",
			"====",
			NULL
		}
	);
	assert(assert_dictpair(dict,
		5,
			"USER", "minishell=GO=",
			"", "helloworld",
			"VERSION", "",
			"", "",
			"", "==="
	));
	dict_free(dict);
	assert(assert_leaks());
}

static void	test_putdict_simple(void)
{
	t_dict	*dict;

	dict = malloc(sizeof(t_dict));
	ft_memset(dict, 0, sizeof(t_dict));
	dict_put(dict, "USER", "minishell", 1);
	dict_put(dict, "ZERO", "0", 1);
	dict_put(dict, "DIGIT", "123456789", 1);
	dict_put(dict, "NOVALUE", "", 0);
	dict_put(dict, "NULLVALUE", NULL, 0);
	assert(assert_dictpair(dict,
		5,
			"USER", "minishell",
			"ZERO", "0",
			"DIGIT", "123456789",
			"NOVALUE", "",
			"NULLVALUE", ""
	));
	dict_free(dict);
	assert(assert_leaks());
}

static void	test_putdict_specialcases(void)
{
	t_dict	*dict;

	dict = malloc(sizeof(t_dict));
	ft_memset(dict, 0, sizeof(t_dict));
	dict_put(dict, "", "minishell", 1);
	dict_put(dict, "USER", "minishell", 1);
	dict_put(dict, "USER", "42", 1);
	dict_put(dict, "Hello", "", 1);
	assert(assert_dictpair(dict,
		3,
			"", "minishell",
			"USER", "42",
			"Hello", ""
	));
	dict_free(dict);
	assert(assert_leaks());
}

static void	test_deldict(void)
{
	t_dict	*dict;

	dict = malloc(sizeof(t_dict));
	ft_memset(dict, 0, sizeof(t_dict));
	dict_put(dict, "1", "minishell", 1);
	dict_put(dict, "USER", "42", 1);
	dict_put(dict, "Hello", "", 1);
	assert(assert_dictpair(dict,
		3,
			"1", "minishell",
			"USER", "42",
			"Hello", ""
	));
	dict_del(dict, "USER");
	assert(assert_dictpair(dict,
		2,
			"1", "minishell",
			"Hello", ""
	));
	dict_del(dict, "1");
	assert(assert_dictpair(dict,
		1,
			"Hello", ""
	));
	dict_del(dict, "Hello");
	assert(assert_dictpair(dict,
		0
	));
	dict_free(dict);
	assert(assert_leaks());
}

static void	test_deldict2(void)
{
	t_dict	*dict;

	dict = malloc(sizeof(t_dict));
	ft_memset(dict, 0, sizeof(t_dict));
	dict_put(dict, "1", "minishell", 1);
	dict_put(dict, "2", "minishell2", 1);
	dict_put(dict, "3", "minishell3", 1);
	dict_put(dict, "USER", "42", 1);
	dict_put(dict, "Hello", "", 1);
	dict_del(dict, "1");
	dict_del(dict, "2");
	dict_del(dict, "Hello");
	assert(assert_dictpair(dict,
		2,
			"3", "minishell3",
			"USER", "42"
	));
	dict_free(dict);
	assert(assert_leaks());
}

static void	test_getdict(void)
{
	t_dict	*dict;

	dict = malloc(sizeof(t_dict));
	ft_memset(dict, 0, sizeof(t_dict));
	dict_put(dict, "1", "minishell", 1);
	dict_put(dict, "USER", "42", 1);
	dict_put(dict, "Hello", "", 1);
	assert(!strcmp("minishell", dict_get(dict, "1")));
	assert(!strcmp("42", dict_get(dict, "USER")));
	assert(!strcmp("", dict_get(dict, "Hello")));
	dict_del(dict, "Hello");
	assert(dict_get(dict, "Hello") == NULL);
	dict_free(dict);
	assert(assert_leaks());
}

int		main(int argc, char *argv[])
{
	do_test(&test_makedict_simple);
	do_test(&test_makedict_specialcases1);
	do_test(&test_putdict_simple);
	do_test(&test_putdict_specialcases);
	do_test(&test_deldict);
	do_test(&test_deldict2);
	do_test(&test_getdict);
	print_test_result(argc, argv[0]);
	return (0);
}
