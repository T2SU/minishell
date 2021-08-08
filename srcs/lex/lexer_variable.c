/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 17:49:17 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 00:52:02 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_parse_variable(t_lexer *lexer, t_list *list)
{
	t_strbuf	strbuf;
	char		c;

	if (!add_lex(kDollar, NULL, list))
		exit_error(get_context()->executable_name, NULL, NULL);
	ft_memset(&strbuf, 0, sizeof(t_strbuf));
	while (TRUE)
	{
		c = lexer->str[++lexer->cursor];
		if (c == '\0')
			break ;
		if (!ft_isalnum(c) && c != '_')
			break ;
		if (!strbuf_append(&strbuf, c))
			exit_error(get_context()->executable_name, NULL, NULL);
	}
	if (strbuf_length(&strbuf) == 0)
		return ;
	if (!add_lex_string(kIdentifier, &strbuf, list))
		exit_error(get_context()->executable_name, NULL, NULL);
}
