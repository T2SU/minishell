/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 22:29:41 by smun              #+#    #+#             */
/*   Updated: 2021/08/19 19:39:56 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dispatch_type(t_tokenizer *t, int t1, int t2, char *chars)
{
	const char	cur = *(t->str);
	const char	next = *(t->str + 1);

	if (next == cur)
	{
		chars[1] = next;
		return (t1);
	}
	return (t2);
}

static int	get_token_type(t_tokenizer *t, char *chars)
{
	chars[0] = *t->str;
	if (*t->str == '<')
		return (dispatch_type(t, kLessLess, '<', chars));
	if (*t->str == '>')
		return (dispatch_type(t, kGreaterGreater, '>', chars));
	if (*t->str == '|')
		return (dispatch_type(t, kBarBar, '|', chars));
	if (*t->str == '&')
		return (dispatch_type(t, kAndAnd, kWord, chars));
	if (*t->str == '(')
		return ('(');
	if (*t->str == ')')
		return (')');
	return (kWord);
}

static t_list	*generate_token(t_tokenizer *t, int type, char *chars)
{
	t_list	*lst;
	t_token	*token;

	token = safe_malloc(sizeof(t_token));
	ft_memset(token, 0, sizeof(t_token));
	lst = ft_lstnew(token);
	if (lst == NULL)
		exit_error();
	if (type == kWord)
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
		if (ft_strchr(" \t\r\n", *tokenizer->str))
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
