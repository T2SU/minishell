/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 17:08:55 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 14:43:05 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	lexer_flush_identifier(t_strbuf *strbuf, t_list *list)
{
	add_lex_string(Lex_Identifier, strbuf, list);
	ft_memset(strbuf, 0, sizeof(t_strbuf));
}

void	lexer_build_identifier(t_strbuf *strbuf, char ch)
{
	if (!strbuf_append(strbuf, ch))
		exit_error(get_context()->executable_name, NULL, NULL);
}
