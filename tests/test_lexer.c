/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:20:08 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 23:07:53 by smun             ###   ########.fr       */
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
	//printf("input=[%s]\n", str);
	print_lexes(&list);
	printf("-----------------------------------\n");
	list_free(&list);
}

static void test_parse_lexes_complex1(void)
{
	parse_lexes("echo $PATH | cat -e > hello.log");
}

static void test_parse_lexes_complex2(void)
{
	parse_lexes("cat << \"Hello\"WORLD`.lo`'g'");
}

static void test_parse_lexes_complex3(void)
{
	parse_lexes("(./run.sh && sudo /usr/bin/make -C \'../sources\' dev) || echo \"$USER has error\" >> `\"hello\".log` && $");
}

static void test_parse_lexes_simple(void)
{
	parse_lexes("\"\\$USER\"");
	parse_lexes("\\$\"USER\"");
	parse_lexes("$\"");
	parse_lexes("$");
	parse_lexes("echo $\"USER\"");
	parse_lexes("echo \"$USER\"");
}

static void test_parse_lexes_simple2(void)
{
	parse_lexes("ls -al");
	parse_lexes("git add .");
	parse_lexes("echo \"Hello World\"");
	parse_lexes("echo \"Hello $USER\"");
}

int		main(int argc, char *argv[])
{
	do_test(&test_parse_string);
	do_test_stdout(&test_parse_lexes_simple,
		"lexes=[1]\n"
		"Lex_String($USER)\n"
		"-----------------------------------\n"
		"lexes=[3]\n"
		"Lex_Identifier(\\), Lex_OuterDollar, Lex_String(USER)\n"
		"-----------------------------------\n"
		"lexes=[2]\n"
		"Lex_OuterDollar, Lex_String(\")\n"
		"-----------------------------------\n"
		"lexes=[1]\n"
		"Lex_OuterDollar\n"
		"-----------------------------------\n"
		"lexes=[4]\n"
		"Lex_Identifier(echo), Lex_Splitter, Lex_OuterDollar, Lex_String(USER)\n"
		"-----------------------------------\n"
		"lexes=[5]\n"
		"Lex_Identifier(echo), Lex_Splitter, Lex_InnerDollar, Lex_Identifier(USER), Lex_String(\")\n"
		"-----------------------------------\n");
	do_test_stdout(&test_parse_lexes_simple2,
		"lexes=[3]\n"
		"Lex_Identifier(ls), Lex_Splitter, Lex_Identifier(-al)\n"
		"-----------------------------------\n"
		"lexes=[5]\n"
		"Lex_Identifier(git), Lex_Splitter, Lex_Identifier(add), Lex_Splitter, Lex_Identifier(.)\n"
		"-----------------------------------\n"
		"lexes=[3]\n"
		"Lex_Identifier(echo), Lex_Splitter, Lex_String(Hello World)\n"
		"-----------------------------------\n"
		"lexes=[6]\n"
		"Lex_Identifier(echo), Lex_Splitter, Lex_String(Hello ), Lex_InnerDollar, Lex_Identifier(USER), Lex_String(\")\n"
		"-----------------------------------\n"
		);
	do_test_stdout(&test_parse_lexes_complex1,
		"lexes=[14]\n"
		"Lex_Identifier(echo), Lex_Splitter, Lex_OuterDollar, Lex_Identifier(PATH), Lex_Splitter, Lex_Bar, Lex_Splitter, Lex_Identifier(cat), Lex_Splitter, Lex_Identifier(-e), Lex_Splitter, Lex_Greater, Lex_Splitter, Lex_Identifier(hello.log)\n"
		"-----------------------------------\n"
		);
	do_test_stdout(&test_parse_lexes_complex2,
		"lexes=[8]\n"
		"Lex_Identifier(cat), Lex_Splitter, Lex_DoubleLesser, Lex_Splitter, Lex_String(Hello), Lex_Identifier(WORLD), Lex_String(.lo), Lex_String(g)\n"
		"-----------------------------------\n"
		);
	do_test_stdout(&test_parse_lexes_complex3,
		"lexes=[31]\n"
		"Lex_OpenBracket, Lex_Identifier(./run.sh), Lex_Splitter, Lex_DoubleAmpersand, Lex_Splitter, Lex_Identifier(sudo), Lex_Splitter, Lex_Identifier(/usr/bin/make), Lex_Splitter, Lex_Identifier(-C), Lex_Splitter, Lex_String(../sources), Lex_Splitter, Lex_Identifier(dev), Lex_CloseBracket, Lex_Splitter, Lex_DoubleBar, Lex_Splitter, Lex_Identifier(echo), Lex_Splitter, Lex_InnerDollar, Lex_Identifier(USER), Lex_String( has error), Lex_Splitter, Lex_DoubleGreater, Lex_Splitter, Lex_String(\"hello\".log), Lex_Splitter, Lex_DoubleAmpersand, Lex_Splitter, Lex_OuterDollar\n"
		"-----------------------------------\n"
		);
	print_test_result(argc, argv[0]);
	return (0);
}
