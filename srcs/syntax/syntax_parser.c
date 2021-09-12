/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 19:03:18 by smun              #+#    #+#             */
/*   Updated: 2021/09/12 17:19:19 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static t_syntax	*validate(t_stack *st)
{
	t_syntax	*syn;
	t_list		*lst;
	t_bool		error;

	error = ft_lstsize(st->dat) != 1;
	if (!error && st->dat && !syntax_is_command(st->dat->content))
		error = TRUE;
	if (!error)
		return (stack_pop(st));
	if (VERBOSE)
	{
		printf(YELLOW"[[Remaining tokens in stack]]\n"RESET);
		lst = st->dat;
		while (lst != NULL)
		{
			syn = lst->content;
			printf("Type=[%d]\n", syn->type);
			syntax_print(syn);
			printf(RESET"\n------\n");
			lst = lst->next;
		}
	}
	ft_lstclear(&st->dat, &dispose_syntax);
	return (NULL);
}

t_syntax	*syntax_parse(t_list *tokens)
{
	t_stack	st;
	t_list	*lst;

	ft_memset(&st, 0, sizeof(t_stack));
	lst = tokens;
	while (TRUE)
	{
		if (!syntax_reassemble(&st) && !syntax_assemble(&st))
		{
			if (lst == NULL)
				break ;
			syntax_build_from_token(&st, lst->content);
			lst = lst->next;
		}
	}
	return (validate(&st));
}

static t_bool	is_emptyline(char *line)
{
	while (*line)
		if (NULL == ft_strchr(" \t\r\n", *(line++)))
			return (FALSE);
	return (TRUE);
}

static void	print_as_verbose(t_syntax *syntax, t_list *tokens)
{
	if (!VERBOSE)
		return ;
	if (syntax == NULL && tokens == NULL)
		return ;
	if (syntax != NULL)
	{
		printf(BLUE"* PARSED SHELL SYNTAX"RESET"\n");
		syntax_print(syntax);
	}
	if (tokens != NULL)
	{
		printf(RED"\n* PARSED TOKENS\n"YELLOW"TYPE   "GREEN"DATA"RESET"\n");
		print_tokens(tokens);
	}
}

int	parse(t_syntax **syntax, char *line)
{
	t_tokenizer	tokenizer;
	t_list		*tokens;

	if (is_emptyline(line))
		return (kEmptyLine);
	tokenizer.str = line;
	tokenizer.quote = 0;
	tokens = tokenize(&tokenizer);
	if (tokens == NULL)
		return (kEmptyLine);
	print_as_verbose(NULL, tokens);
	*syntax = syntax_parse(tokens);
	ft_lstclear(&tokens, dispose_token);
	print_as_verbose(*syntax, NULL);
	if (*syntax == NULL)
		return (kFailed);
	if (VERBOSE)
		printf(GREEN"\n\n* EXECUTION RESULT"RESET"\n");
	return (kSuccess);
}
