/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_syntax1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:16:19 by smun              #+#    #+#             */
/*   Updated: 2021/08/17 18:46:37 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testlib.h"
#include "minishell.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static void test_syntax(const char *cmd)
{
	t_statement	*statement;

	statement = parse(cmd);
	if (statement != NULL)
		print_statement(statement);
	printf("\n");
}

int main(int argc, char *argv[])
{
	test_syntax("echo");
	test_syntax("echo hello world");
	test_syntax("echo \"hello world\"");
	test_syntax("echo \"hello \"world\"");
	test_syntax("echo \"hello \\\"world\"asdf aa  ");
	test_syntax("echo \"h'''el\\n\\'\\f\\a\\b     ");
	test_syntax("echo hello > a");
	test_syntax("echo hello > a b c d");
	test_syntax("echo hello > a b c d");
	test_syntax("echo hello > a b > c d e > f > g > h");
	test_syntax("echo hello>a b>c d e>f >g> h");
	test_syntax("echo hello | cat");
	test_syntax("echo hello>a b>c d |hexdump e>f | cat >g> h");
	test_syntax("(echo hello)");
	test_syntax("(echo hello) && cat");
	test_syntax("(echo hello && cat) || hexdump");
	test_syntax("(echo hello && cat && (true || false)) || hexdump > c d e < d >> e h f > g2 g << f | gello && echo hello world > g f d | da d");
	(void)argc;
	(void)argv;
	//print_test_result(argc, argv[0]);
}
