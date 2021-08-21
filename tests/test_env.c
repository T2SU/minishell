/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 21:44:28 by smun              #+#    #+#             */
/*   Updated: 2021/08/21 22:44:01 by smun             ###   ########.fr       */
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

static void	test_runenv_normal(void)
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
	assert(run_env(dict));
	dict_free(dict);
	assert(assert_leaks());
}

static void	test_runenv_empty(void)
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
	dict_del(dict, "USER");
	dict_del(dict, "VERSION");
	assert(run_env(dict));
	dict_free(dict);
	assert(assert_leaks());
}

static void	test_runenv_special(void)
{
	t_dict	*dict;

	dict = make_dict(
		(char*[])
		{
			"=minishell",
			"VERSION=",
			"=====",
			NULL
		}
	);
	assert(run_env(dict));
	dict_free(dict);
	assert(assert_leaks());
}

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

static void	test_run_unset_normal(void)
{
	t_dict	*dict;
	t_list	*lst;

	dict = make_dict(
		(char*[])
		{
			"USER=minishell",
			"VERSION1=1.2",
			"VERSION2=1.3",
			"VERSION3=1.4",
			"VERSION4=1.5",
			"USER2=42seoul",
			NULL
		}
	);
	lst = simple_list(3, ft_strdup("USER"), ft_strdup("VERSION1"), ft_strdup("USER2"));
	run_unset(dict, lst);
	assert(run_env(dict));
	dict_free(dict);
	ft_lstclear(&lst, &free);
	assert(assert_leaks());
}

int		main(int argc, char *argv[])
{
	do_test_stdout(&test_runenv_normal,
		"USER=minishell\n"
		"VERSION=1.1\n"
	);
	do_test_stdout(&test_runenv_empty,
		""
	);
	do_test_stdout(&test_runenv_special,
		"=minishell\n"
		"VERSION=\n"
		"=====\n"
	);
	do_test_stdout(&test_run_unset_normal,
		"VERSION2=1.3\n"
		"VERSION3=1.4\n"
		"VERSION4=1.5\n"
	);
	print_test_result(argc, argv[0]);
	return (0);
}
