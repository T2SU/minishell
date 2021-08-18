/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 22:29:41 by smun              #+#    #+#             */
/*   Updated: 2021/08/18 18:33:07 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dispatch_type(t_tokenizer *t, int t1, int t2, char *chars)
{
	const char	cur = *(t->str);
	const char	next = *(t->str + 1);

	if (next == cur)
	{
		t->str++;
		chars[1] = next;
		return (t1);
	}
	return (t2);
}

static int	get_token_type(t_tokenizer *t, char *chars)
{
	chars[0] = *t->str;
	if (*t->str == '>')
		return (dispatch_type(t, Token_LessLess, Token_Less, chars));
	if (*t->str == '<')
		return (dispatch_type(t, Token_GreaterGreater, Token_Greater, chars));
	if (*t->str == '|')
		return (dispatch_type(t, Token_BarBar, Token_Bar, chars));
	if (*t->str == '&')
		return (dispatch_type(t, Token_AndAnd, Token_Word, chars));
	if (*t->str == '(')
		return (Token_Open);
	if (*t->str == ')')
		return (Token_Close);
	return (Token_Word);
}

static t_list	*generate_token(t_tokenizer *t, int type, char *chars)
{
	t_list	*lst;
	t_token	*token;

	token = malloc(sizeof(t_token));
	lst = ft_lstnew(token);
	if (lst == NULL || token == NULL)
		exit_error();
	if (type == Token_Word)
		token->word = get_word(t);
	else
	{
		ft_memcpy(token->chars, chars, sizeof(token->chars));
		t->str += ft_strlen(chars);
	}
	token->type = type;
	return (lst);
}

t_list	*tokenize(t_tokenizer *tokenizer)
{
	t_list	*lst;
	int		type;
	char	chars[3];

	lst = NULL;
	while (*tokenizer->str)
	{
		if (*tokenizer->str == ' ' || *tokenizer->str == '\t')
		{
			tokenizer->str++;
			continue ;
		}
		ft_memset(chars, 0, sizeof(chars));
		type = get_token_type(tokenizer, chars);
		ft_lstadd_back(&lst, generate_token(tokenizer, type, chars));
	}
	return (lst);
}
