/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 22:29:08 by smun              #+#    #+#             */
/*   Updated: 2021/08/22 19:04:37 by hkim             ###   ########.fr       */
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

static t_list *simple_list(int count, ...)
{
	va_list ap;
	t_list	*ret;

	ret = NULL;
	va_start(ap, count);
	for (int i = 0; i < count; i++)
		ft_lstadd_back(&ret, ft_lstnew(va_arg(ap, char*)));
	va_end(ap);
	return (ret);
}

static void	test_runexport_noargs_simple(void)
{
	t_dict	*dict;

	dict = make_dict(
		(char*[])
		{
			"USER=42seoul",
			"PATH=/usr/bin:/usr/sbin",
			"HOME=/Users/42seoul",
			NULL
		}
	);
	run_export(dict, NULL);
	dict_free(dict);
	assert(assert_leaks());
}

static void	test_runexport_args_simple(void)
{
	t_dict	*dict;
	t_list	*lst;

	dict = make_dict(
		(char*[])
		{
			"AEST1=GO",
			"TEST2=GOGO",
			"ZEST3=GOGOGO",
			NULL
		}
	);
	lst = simple_list(3, ft_strdup("USER=42seoul"), ft_strdup("PATH=/usr/bin:/usr/sbin"), ft_strdup("HOME=/Users/42seoul"));
	run_export(dict, lst);
	assert(assert_dictpair(dict,
		6,
			"AEST1", "GO",
			"TEST2", "GOGO",
			"ZEST3", "GOGOGO",
			"USER", "42seoul",
			"PATH", "/usr/bin:/usr/sbin",
			"HOME", "/Users/42seoul"
	));
	dict_free(dict);
	ft_lstclear(&lst, &free);
	assert(assert_leaks());
}

static void	test_runexport_args_and_noargs_simple(void)
{
	t_dict	*dict;
	t_list	*lst;

	dict = make_dict(
		(char*[])
		{
			"AEST1=GO",
			"TEST2=GOGO",
			"ZEST3=GOGOGO",
			NULL
		}
	);
	lst = simple_list(3, ft_strdup("USER=42seoul"), ft_strdup("PATH=/usr/bin:/usr/sbin"), ft_strdup("HOME=/Users/42seoul"));
	run_export(dict, lst);
	run_export(dict, NULL);
	dict_free(dict);
	ft_lstclear(&lst, &free);
	assert(assert_leaks());
}

static void	test_runexport_args_and_noargs_special(void)
{
	t_dict	*dict;
	t_list	*lst;

	dict = make_dict(
		(char*[])
		{
			"AEST1=GO",
			NULL
		}
	);
	lst = simple_list(5,
		ft_strdup("USER========123456"),
		ft_strdup("PATH=\"G\"B$==Z\\X'"),
		ft_strdup("HOME=/U se    r  s/42 s e ou l"),
		ft_strdup("Z=\\\"\\$\\\\GGHH\\1\\2\\3"),
		ft_strdup("ONLYKEY")
	);
	run_export(dict, lst);
	run_export(dict, NULL);
	dict_free(dict);
	ft_lstclear(&lst, &free);
	assert(assert_leaks());
}

int		main(int argc, char *argv[])
{
	do_test_stdout(&test_runexport_noargs_simple,
		"declare -x HOME=\"/Users/42seoul\"\n"
		"declare -x PATH=\"/usr/bin:/usr/sbin\"\n"
		"declare -x USER=\"42seoul\"\n"
	);
	do_test(&test_runexport_args_simple);
	do_test_stdout(&test_runexport_args_and_noargs_simple,
		"declare -x AEST1=\"GO\"\n"
		"declare -x HOME=\"/Users/42seoul\"\n"
		"declare -x PATH=\"/usr/bin:/usr/sbin\"\n"
		"declare -x TEST2=\"GOGO\"\n"
		"declare -x USER=\"42seoul\"\n"
		"declare -x ZEST3=\"GOGOGO\"\n"
	);
	do_test_stdout(&test_runexport_args_and_noargs_special,
		"declare -x AEST1=\"GO\"\n"
		"declare -x HOME=\"/U se    r  s/42 s e ou l\"\n"
		"declare -x ONLYKEY\n"
		"declare -x PATH=\"\\\"G\\\"B\\$==Z\\\\X'\"\n"
		"declare -x USER=\"=======123456\"\n"
		"declare -x Z=\"\\\\\\\"\\\\\\$\\\\\\\\GGHH\\\\1\\\\2\\\\3\"\n"
	);
	print_test_result(argc, argv[0]);
	return (0);
}
