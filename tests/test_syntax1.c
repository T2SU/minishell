/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_syntax1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:16:19 by smun              #+#    #+#             */
/*   Updated: 2021/08/17 15:44:10 by smun             ###   ########.fr       */
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
	test_syntax("echo hello world");
	test_syntax("echo \"hello world\"");
	test_syntax("echo \"hello \"world\"");
	test_syntax("echo \"hello \\\"world\"asdf aa  ");
	(void)argc;
	(void)argv;
	//print_test_result(argc, argv[0]);
}
