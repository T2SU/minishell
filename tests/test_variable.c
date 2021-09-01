/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_variable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 15:35:05 by smun              #+#    #+#             */
/*   Updated: 2021/08/31 17:24:42 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testlib.h"
#include "minishell.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

static void test_variable(void)
{
	t_tokenizer	tokenizer;
	t_list	*tokens;
	t_list	*lst;
	t_token	*token;

	tokenizer.quote = 0;
	tokenizer.str = "$US";
	tokens = tokenize(&tokenizer);

	lst = tokens;
	while (lst != NULL)
	{
		token = lst->content;
		char *w = word_get(token->word, TRUE, FALSE);
		printf("%s\n", w);
		lst = lst->next;
	}
	ft_lstclear(&tokens, dispose_token);
}

static void test_expand_wildcard(void)
{
	t_list	*lst;
	char	**array;
	int		i;

	lst = NULL;
	expand_wildcard(&lst);
	array = convert_to_array(lst);
	i = 0;
	while (array[i] != NULL)
	{
		printf("%s\n", array[i]);
		free(array[i]);
		i++;
	}
	free(array);
}

int main(int argc, char *argv[], char *envp[])
{
	context_init(argv, envp);
	test_variable();
	test_expand_wildcard();
	print_test_result(argc, argv[0]);
	return (0);
}
