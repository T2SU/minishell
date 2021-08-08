/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_lex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 00:29:42 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 00:32:03 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

t_bool	add_lex(int type, char *data, t_list *list)
{
	t_lex	*lex;

	lex = malloc(sizeof(t_lex));
	if (lex == NULL)
		return (FALSE);
	lex->type = type;
	lex->data = data;
	if (!list_add(list, lex, &free))
		return (FALSE);
	return (TRUE);
}

static void		free_lex_string(void *ptr)
{
	t_lex	*lex;

	lex = (t_lex *)ptr;
	free(lex->data);
	free(lex);
}

t_bool	add_lex_string(int type, t_strbuf *strbuf, t_list *list)
{
	t_lex	*lex;
	char	*str;

	str = strbuf_get(strbuf, TRUE);
	if (str == NULL)
		return (FALSE);
	lex = malloc(sizeof(t_lex));
	if (lex == NULL)
		return (FALSE);
	lex->type = type;
	lex->data = str;
	if (!list_add(list, lex, &free_lex_string))
		return (FALSE);
	return (TRUE);
}
