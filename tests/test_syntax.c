/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 18:03:24 by smun              #+#    #+#             */
/*   Updated: 2021/08/19 14:54:13 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testlib.h"
#include "minishell.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static void	test_simple2(void)
{
	t_tokenizer	tokenizer;
	t_list		*tokens;
	t_syntax	*syntax;

	tokenizer.quote = 0;
	tokenizer.str = "(ER >> dd << dd g f | cat < b < gogo $US>>ER| A$B\"C\" > dd && (true || false | (go $A << gos)))|cat 43a sda<<dso>das ddd g\"$'sd\"s'";

	tokens = tokenize(&tokenizer);
	print_tokens(tokens);
	syntax = syntax_parse(tokens);
	if (syntax == NULL)
		printf("syntax error\n");
	ft_lstclear(&tokens, &dispose_token);
	syntax_print(syntax);
	printf(RESET"\n");
	dispose_syntax(syntax);
}

int		main(void)
{
	test_simple2();
	return (0);
}
