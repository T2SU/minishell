/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:20:08 by smun              #+#    #+#             */
/*   Updated: 2021/08/04 15:39:12 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testlib.h"
#include "minishell.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

static void	test_parse_string(void)
{
	t_lexer	lexer;
	t_list	list;

	memset(&lexer, 0, sizeof(t_lexer));
	memset(&list, 0, sizeof(t_list));
	lexer.str = "\"Hello World' d\"  gogo";
	assert(lexer_parse_string(&lexer, &list));
	assert(list.length == 1);
	lexer.cursor = 0;
	lexer.str = "\"Hello World' d  gogo";
	assert(lexer_parse_string(&lexer, &list));
	assert(list.length == 2);

	t_lex *lex = (t_lex *)list.head->data;
	(void)lex;

	list_free(&list);
}

int		main(int argc, char *argv[])
{
	test_parse_string();
	//do_test(&test_parse_string);
	print_test_result(argc, argv[0]);
	return (0);
}
