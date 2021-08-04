/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 17:49:17 by smun              #+#    #+#             */
/*   Updated: 2021/08/04 17:49:59 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_parse_variable(t_lexer *lexer, t_list *list)
{
	if (!add_lex(kVariable, 0, list))
		exit_error(get_context()->executable_name, NULL, NULL);
}
