/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 22:29:41 by smun              #+#    #+#             */
/*   Updated: 2021/08/17 15:46:46 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	consecutive_chars(t_tokenizer *t, int t1, int t2, char *chars)
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

static int	escape_sequence(t_tokenizer *t, char *chars)
{
	const char	next = *(t->str + 1);

	if (next == '\'' && t->quote == Token_Quote)
	{
		chars[0] = *(++t->str);
		return (Token_Character);
	}
	if (next == '"' && t->quote == Token_DoubleQuote)
	{
		chars[0] = *(++t->str);
		return (Token_Character);
	}
	return (Token_Character);
}

static int	get_token_type(t_tokenizer *t, char *chars)
{
	chars[0] = *t->str;
	if (*t->str == '\'')
		return (Token_Quote);
	if (*t->str == '\"')
		return (Token_DoubleQuote);
	if (*t->str == '$')
		return (Token_Dollar);
	if (t->quote == 0 && (*t->str == ' ' || *t->str == '\t'))
		return (Token_WhiteSpace);
	if (*t->str == '\\')
		return (escape_sequence(t, chars));
	if (*t->str == '(')
		return (Token_OpenBracket);
	if (*t->str == ')')
		return (Token_CloseBracket);
	if (*t->str == '>')
		return (consecutive_chars(t, Token_Append, Token_Write, chars));
	if (*t->str == '<')
		return (consecutive_chars(t, Token_ReadDelim, Token_Read, chars));
	if (*t->str == '|')
		return (consecutive_chars(t, Token_Or, Token_Bar, chars));
	if (*t->str == '&')
		return (consecutive_chars(t, Token_And, Token_Character, chars));
	return (Token_Character);
}

static t_list	*new_token_list(int type, char *chars)
{
	t_list	*lst;
	t_token	*token;

	token = malloc(sizeof(t_token));
	lst = ft_lstnew(token);
	if (lst == NULL || token == NULL)
		exit_error();
	ft_memcpy(token->data, chars, sizeof(token->data));
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
		ft_memset(chars, 0, sizeof(chars));
		type = get_token_type(tokenizer, chars);
		ft_lstadd_back(&lst, new_token_list(type, chars));
		if (type == Token_DoubleQuote || type == Token_Quote)
			if (tokenizer->quote == type || tokenizer->quote == 0)
				tokenizer->quote ^= type;
		tokenizer->str++;
	}
	return (lst);
}
