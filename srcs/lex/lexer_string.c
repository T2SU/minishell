/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 23:32:52 by smun              #+#    #+#             */
/*   Updated: 2021/08/04 15:31:42 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void		free_lex_string(void *ptr)
{
	t_lex	*lex;

	lex = (t_lex *)ptr;
	free(lex->data.identifier.data);
	free(lex);
}

static t_bool	add_lex_string(char *str, t_list *list)
{
	t_lex	*lex;

	lex = malloc(sizeof(t_lex));
	if (lex == NULL)
		return (FALSE);
	lex->type = kString;
	lex->data.identifier.data = str;
	list_add(list, lex, &free_lex_string);
	return (TRUE);
}

t_bool	lexer_parse_string(t_lexer *lexer, t_list *list)
{
	const char	*begin;
	const char	*end;
	char		*str;
	char		c;
	size_t		len;

	c = lexer->str[lexer->cursor];
	if (c != '\'' && c != '\"' && c != '`')
		return (FALSE);
	begin = &lexer->str[lexer->cursor];
	end = ft_strchr(begin + 1, c);
	if (end == NULL)
		end = begin + ft_strlen(begin);
	len = (size_t)(end - begin + 1);
	str = malloc(len + 1);
	if (str == NULL)
		exit_error(get_context()->executable_name, NULL, NULL);
	ft_memcpy(str, begin, len);
	str[len] = '\0';
	if (!add_lex_string(str, list))
		exit_error(get_context()->executable_name, NULL, NULL);
	lexer->cursor += len;
	return (TRUE);
}
