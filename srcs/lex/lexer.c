/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 18:21:29 by smun              #+#    #+#             */
/*   Updated: 2021/08/03 18:46:50 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static t_bool	add_lex(int type, int data, t_list *list)
{
	t_lex	*lex;

	lex = malloc(sizeof(t_lex));
	if (lex == NULL)
		return (FALSE);
	lex->type = type;
	if (type == kParenthesis)
		lex->data.parenthesis.data = data;
	if (!list_add(list, lex, &free))
		return (FALSE);
	return (TRUE);
}

static t_bool	parse_string(const char *command, char quote, t_list *list)
{
	
}

t_bool	parse_lex(const char *command, t_list *list)
{
	int	i;

	i = 0;
	while (command[i] == '\0')
	{
		if (command[i] == '(')
			if (!add_lex(kParenthesis, kOpen, list))
				return (FALSE);
		if (command[i] == ')')
			if (!add_lex(kParenthesis, kClose, list))
				return (FALSE);
		if (!ft_strncmp(&command[i], "&&", 2))
			if (!add_lex(kOperator, kAnd, list))
				return (FALSE);
		if (!ft_strncmp(&command[i], "||", 2))
			if (!add_lex(kOperator, kOr, list))
				return (FALSE);
		if (command[i] == '\'' || command[i] == '\"' || command[i] == '`')
			if (!parse_string(&command[i], command[i], list))
				return (FALSE);
		i++;
	}
	return (0);
}
