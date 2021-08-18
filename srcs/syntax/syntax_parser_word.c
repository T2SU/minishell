/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parser_word.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 22:51:30 by smun              #+#    #+#             */
/*   Updated: 2021/08/18 16:40:22 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_quote(int type)
{
	if (type == Token_Quote)
		return (TRUE);
	if (type == Token_DoubleQuote)
		return (TRUE);
	return (FALSE);
}

char	*get_word(t_parser *parser)
{
	t_strbuf	strbuf;
	t_token		*token;

	ft_memset(&strbuf, 0, sizeof(t_strbuf));
	while (parser->cur != NULL)
	{
		token = parser->cur->content;
		if (token->type != Token_Character && !is_quote(token->type))
			break ;
		strbuf_appends(&strbuf, token->data);
		parser->cur = parser->cur->next;
	}
	if (strbuf_length(&strbuf) == 0)
		return (NULL);
	return strbuf_get(&strbuf, TRUE);
}
