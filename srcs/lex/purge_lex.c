/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   purge_lex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 19:51:29 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 22:54:51 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void	build_and_add(t_list *new_list, t_strbuf *strbuf, t_elem *elem)
{
	char	*str;

	if (strbuf_length(strbuf) == 0)
		return ;
	str = strbuf_get(strbuf, TRUE);
	if (str == NULL)
		exit_error(get_context()->executable_name);
	if (!list_add(new_list, str, &free))
		exit_error(get_context()->executable_name);
	ft_memset(strbuf, 0, sizeof(t_strbuf));
	if (!list_add(new_list, elem->data, elem->destructor))
		exit_error(get_context()->executable_name);
}

static void	append(t_strbuf *strbuf, t_lex *lex)
{
	if (!strbuf_appends(strbuf, lex->data))
		exit_error(get_context()->executable_name);
	free(lex->data);
	free(lex);
}

void	purge_lexes(t_list *list)
{
	t_list		new_list;
	t_elem		*cur;
	t_lex		*lex;
	t_strbuf	strbuf;

	ft_memset(&new_list, 0, sizeof(t_list));
	ft_memset(&strbuf, 0, sizeof(t_strbuf));
	cur = list->head;
	while (cur != NULL)
	{
		lex = cur->data;
		if (lex->type == Lex_Identifier || lex->type == Lex_String)
			append(&strbuf, lex);
		else
			build_and_add(&new_list, &strbuf, cur);
		cur = cur->next;
	}
	build_and_add(&new_list, &strbuf, cur);
	*list = new_list;
}
