/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_lex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 00:29:42 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 21:25:51 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	add_lex(int type, char *data, t_list *list)
{
	t_lex	*lex;

	lex = malloc(sizeof(t_lex));
	if (lex == NULL)
		exit_error(get_context()->executable_name);
	lex->type = type;
	lex->data = data;
	if (!list_add(list, lex, &free))
		exit_error(get_context()->executable_name);
}

static void		free_lex_string(void *ptr)
{
	t_lex	*lex;

	lex = (t_lex *)ptr;
	free(lex->data);
	free(lex);
}

void	add_lex_string(int type, t_strbuf *strbuf, t_list *list)
{
	t_lex	*lex;
	char	*str;

	if (strbuf_length(strbuf) == 0)
		return ;
	str = strbuf_get(strbuf, TRUE);
	if (str == NULL)
		exit_error(get_context()->executable_name);
	lex = malloc(sizeof(t_lex));
	if (lex == NULL)
		exit_error(get_context()->executable_name);
	lex->type = type;
	lex->data = str;
	if (!list_add(list, lex, &free_lex_string))
		exit_error(get_context()->executable_name);
}
