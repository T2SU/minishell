/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 20:08:19 by hkim              #+#    #+#             */
/*   Updated: 2021/08/23 21:31:04 by hkim             ###   ########.fr       */
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

static void test_run_pwd(void)
{
	run_pwd();
	assert(assert_leaks());
}

static void test_run_cd_one_arg()
{
	t_list	*list;
	t_dict	*dict;
	char	*home;

	dict = make_dict(
		(char*[])
		{
			"HOME=/home/hkim",
			NULL
		}
	);
	home = dict_get(dict, "HOME");
	list = NULL;
	ft_lstadd_back(&list, ft_lstnew("../"));
	run_cd(list, home);
	run_pwd();
	dict_free(dict);
	free(list);
	assert(assert_leaks());
}

static void test_run_cd_no_arg()
{
	t_list	*list;
	t_dict	*dict;
	char	*home;

	dict = make_dict(
		(char*[])
		{
			"HOME=/home/hkim",
			NULL
		}
	);
	home = dict_get(dict, "HOME");
	list = NULL;
	run_cd(list, home);
	run_pwd();
	dict_free(dict);
	free(list);
	assert(assert_leaks());
}

static void test_run_cd_wrong_path()
{
	t_list	*list;
	t_dict	*dict;
	char	*home;

	dict = make_dict(
		(char*[])
		{
			"HOME=/home/hkim",
			NULL
		}
	);
	home = dict_get(dict, "HOME");
	list = NULL;
	ft_lstadd_back(&list, ft_lstnew("notexist"));
	run_cd(list, home);
	dict_free(dict);
	free(list);
	assert(assert_leaks());
}

static void test_run_cd_several_arg()
{
	t_list	*list;
	t_dict	*dict;
	char	*home;

	dict = make_dict(
		(char*[])
		{
			"HOME=/home/hkim",
			NULL
		}
	);
	home = dict_get(dict, "HOME");
	list = NULL;
	ft_lstadd_back(&list, ft_lstnew("../"));
	ft_lstadd_back(&list, ft_lstnew("test"));
	run_cd(list, home);
	dict_free(dict);
	free(list->next);
	free(list);
	assert(assert_leaks());
}

static void test_run_exit_no_args()
{
	run_exit(NULL);
}

static void test_run_exit_one_args()
{
	t_list	*list;

	list = NULL;
	ft_lstadd_back(&list, ft_lstnew("0"));
	run_exit(list);
}

static void test_run_exit_several_args()
{
	t_list	*list;

	list = NULL;
	ft_lstadd_back(&list, ft_lstnew("2"));
	ft_lstadd_back(&list, ft_lstnew("3"));
	run_exit(list);
}

int		main(int argc, char *argv[])
{
	do_test_stdout(&test_run_pwd,
		"/home/hkim/mycode/dict/tests\n"
	);
	do_test_stdout(&test_run_cd_one_arg,
		"/home/hkim/mycode/dict\n"
	);
	do_test_stdout(&test_run_cd_no_arg,
		"/home/hkim\n"
	);
	do_test_stdout(&test_run_cd_wrong_path,
		"cd: notexist: No such file or directory\n"
	);
	do_test_stdout(&test_run_cd_several_arg,
		"cd: too many arguments\n"
	);
	do_test_stdout(&test_run_exit_no_args,
		"exit\n"
	);
	do_test_stdout(&test_run_exit_one_args,
		"exit\n"
	);
	do_test_stdout(&test_run_exit_several_args,
		"exit\n"
		"exit: too many arguments\n"
	);
	print_test_result(argc, argv[0]);
	return (0);
}
