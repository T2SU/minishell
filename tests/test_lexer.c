/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:20:08 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 01:32:36 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testlib.h"
#include "minishell.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static t_bool	parse_string_as_lex(const char *str, const char *expected)
{
	t_lexer	lexer;
	t_list	list;
	t_lex 	*lex;

	memset(&lexer, 0, sizeof(t_lexer));
	memset(&list, 0, sizeof(t_list));
	lexer.str = str;
	lexer_parse_string(&lexer, &list);
	if (list.length != 1)
		return (FALSE);
	lex = (t_lex *)list.head->data;
	if (strcmp(lex->data, expected))
		return (FALSE);
	list_free(&list);
	return (TRUE);
}

static void	test_parse_string(void)
{
	assert(parse_string_as_lex("\"Hello World \" gogo", "Hello World "));
	assert(parse_string_as_lex("\"Hello \\\" GoGo\"   ", "Hello \" GoGo"));
	assert(parse_string_as_lex("\"Hello ' \\\\ GoGo\"   ", "Hello ' \\ GoGo"));
	assert(parse_string_as_lex("\"Hi\\", "Hi\\"));
}

static void	parse_lexes(const char *str)
{
	t_list	list;

	memset(&list, 0, sizeof(t_list));
	parse_lex(str, &list);
	printf("input=[%s]\n", str);
	print_lexes(&list);
	printf("-----------------------------------\n");
	list_free(&list);
}

static void test_parse_lexes(void)
{
	parse_lexes("\"\\$USER\"");
	parse_lexes("\\$\"USER\"");
	parse_lexes("$\"");
	parse_lexes("$");
	parse_lexes("echo $\"USER\"");
	parse_lexes("echo \"$USER\"");
	parse_lexes("ls -al");
	parse_lexes("git add .");
	parse_lexes("echo \"Hello World\"");
	parse_lexes("echo \"Hello $USER\"");
	parse_lexes("echo $PATH | cat -e > hello.log");
	parse_lexes("cat << \"Hello\"WORLD`.lo`'g'");
	parse_lexes("(./run.sh && sudo /usr/bin/make -C \'../sources\' dev) || echo \"$USER has error\" >> `\"hello\".log` && $");
}

int		main(int argc, char *argv[])
{
	//do_test(&test_parse_string);
	test_parse_string();
	(void)argc;
	(void)argv;
	//print_test_result(argc, argv[0]);
	test_parse_lexes();
	return (0);
}
