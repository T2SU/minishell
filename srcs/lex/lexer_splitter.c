/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_splitter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 17:08:55 by smun              #+#    #+#             */
/*   Updated: 2021/08/04 17:17:40 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_parse_splitter(t_lexer *lexer, t_list *list)
{
	const char	ch = lexer->str[lexer->cursor];

	if (!add_lex(kSplitter, 0, list))
		exit_error(get_context()->executable_name, NULL, NULL);
	lexer->cursor++;
}
