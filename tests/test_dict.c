/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_dict.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 23:14:30 by smun              #+#    #+#             */
/*   Updated: 2021/08/21 19:42:45 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testlib.h"
#include "functions.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

static t_bool	assert_leaks(void);
static t_bool	assert_dictpair(t_dict *dict, int size, ...);

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
	dict_put(dict, "USER", "minishell");
	dict_put(dict, "ZERO", "0");
	dict_put(dict, "DIGIT", "123456789");
	assert(assert_dictpair(dict,
		3,
			"USER", "minishell",
			"ZERO", "0",
			"DIGIT", "123456789"
	));
	dict_free(dict);
	assert(assert_leaks());
}

static void	test_putdict_specialcases(void)
{
	t_dict	*dict;

	dict = malloc(sizeof(t_dict));
	ft_memset(dict, 0, sizeof(t_dict));
	dict_put(dict, "", "minishell");
	dict_put(dict, "USER", "minishell");
	dict_put(dict, "USER", "42");
	dict_put(dict, "Hello", "");
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
	dict_put(dict, "1", "minishell");
	dict_put(dict, "USER", "42");
	dict_put(dict, "Hello", "");
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

static void	test_getdict(void)
{
	t_dict	*dict;

	dict = malloc(sizeof(t_dict));
	ft_memset(dict, 0, sizeof(t_dict));
	dict_put(dict, "1", "minishell");
	dict_put(dict, "USER", "42");
	dict_put(dict, "Hello", "");
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
	do_test(&test_getdict);
	print_test_result(argc, argv[0]);
	return (0);
}

static t_bool	assert_dictpair(t_dict *dict, int size, ...)
{
	va_list	ap;
	t_bool	ret;
	t_list	*lst;
	t_pair	*pair;
	char	*exstr;

	if (ft_lstsize(dict->head) != size)
	{
		dprintf(STDERR_FILENO, "not equal elements count. expected: %d (your:%d)\n", size, ft_lstsize(dict->head));
		return (FALSE);
	}
	va_start(ap, size);
	ret = TRUE;
	lst = dict->head;
	while (lst != NULL)
	{
		pair = lst->content;
		exstr = va_arg(ap, char*);
		if (strcmp(pair->key, exstr))
		{
			dprintf(STDERR_FILENO, "failed validate pair key. expected: {%s} (your:{%s})\n", exstr, pair->key);
			ret = FALSE;
			break;
		}
		exstr = va_arg(ap, char*);
		if (strcmp(pair->value, exstr))
		{
			dprintf(STDERR_FILENO, "failed validate pair value. expected: {%s} (your:{%s})\n", exstr, pair->key);
			ret = FALSE;
			break;
		}
		lst = lst->next;
	}
	va_end(ap);
	return (ret);
}

static t_bool	assert_leaks(void)
{
	char	buffer[260];

	buffer[0] = 0;
	sprintf(buffer, "leaks %d | grep \"ROOT LEAK\"", getpid());
	if (EXIT_SUCCESS == system(buffer))
	{
		dprintf(STDERR_FILENO, "memory leak occured.\n");
		return (FALSE);
	}
	return (TRUE);
}
