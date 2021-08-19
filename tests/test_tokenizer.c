/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 18:03:24 by smun              #+#    #+#             */
/*   Updated: 2021/08/19 14:54:20 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testlib.h"
#include "minishell.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static void	test_simple1(void)
{
	t_tokenizer	tokenizer;
	t_list		*tokens;

	tokenizer.quote = 0;
	tokenizer.str = "hello \"wor\"rd$USER'gogo'  ";

	tokens = tokenize(&tokenizer);
	print_tokens(tokens);
	ft_lstclear(&tokens, &dispose_token);
}

static void	test_simple2(void)
{
	t_tokenizer	tokenizer;
	t_list		*tokens;

	tokenizer.quote = 0;
	tokenizer.str = "$US>ER";

	tokens = tokenize(&tokenizer);
	print_tokens(tokens);
	ft_lstclear(&tokens, &dispose_token);
}

static void	test_simple3(void)
{
	t_tokenizer	tokenizer;
	t_list		*tokens;

	tokenizer.quote = 0;
	tokenizer.str = "echo $USER> 'c'a\"t\"| hex -C>Fantasy|h'e'llo";

	tokens = tokenize(&tokenizer);
	print_tokens(tokens);
	ft_lstclear(&tokens, &dispose_token);
}

static void	test_simple4(void)
{
	t_tokenizer	tokenizer;
	t_list		*tokens;

	tokenizer.quote = 0;
	tokenizer.str = "'hello'>go$?go";

	tokens = tokenize(&tokenizer);
	print_tokens(tokens);
	ft_lstclear(&tokens, &dispose_token);
}

static void	test_simple5(void)
{
	t_tokenizer	tokenizer;
	t_list		*tokens;

	tokenizer.quote = 0;
	tokenizer.str = "echo $USER<< 'c'a\"t\"| hex -C<Fantasy|h'e'l(l) && (hello || gog | g'\\l' \\\" \")o\"&";

	tokens = tokenize(&tokenizer);
	print_tokens(tokens);
	ft_lstclear(&tokens, &dispose_token);
}

int		main(void)
{
	test_simple4();
	test_simple1();
	test_simple2();
	test_simple3();
	test_simple5();
	return (0);
}
