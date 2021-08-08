/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:20:08 by smun              #+#    #+#             */
/*   Updated: 2021/08/08 23:46:03 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testlib.h"
#include "minishell.h"
#include <assert.h>
#include <string.h>
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

int		main(int argc, char *argv[])
{
	do_test(&test_parse_string);
	print_test_result(argc, argv[0]);
	return (0);
}
