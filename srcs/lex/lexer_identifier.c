/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 17:08:55 by smun              #+#    #+#             */
/*   Updated: 2021/08/04 17:47:33 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	lexer_flush_identifier(t_strbuf *strbuf, t_list *list)
{
	char	*str;

	str = strbuf_get(strbuf, TRUE);
	if (str == NULL)
		exit_error(get_context()->executable_name, NULL, NULL);
	if (ft_strlen(str) > 0)
	{
		if (!add_lex_string(kIdentifier, str, list))
			exit_error(get_context()->executable_name, NULL, NULL);
	}
	else
		free(str);
	ft_memset(strbuf, 0, sizeof(t_strbuf));
}

void	lexer_build_identifier(t_strbuf *strbuf, char ch)
{
	if (!strbuf_append(strbuf, ch))
		exit_error(get_context()->executable_name, NULL, NULL);
}
