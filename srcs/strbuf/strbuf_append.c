/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strbuf_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 16:11:11 by smun              #+#    #+#             */
/*   Updated: 2021/08/17 17:22:58 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_strchunk	*new_chunk(void)
{
	t_strchunk	*chunk;

	chunk = malloc(sizeof(t_strchunk));
	if (chunk == NULL)
		return (NULL);
	ft_memset(chunk, 0, sizeof(t_strchunk));
	return (chunk);
}

static t_bool	should_new_chunk(t_strbuf *strbuf)
{
	t_strchunk	*chunk;

	if (strbuf->head == NULL)
		return (TRUE);
	chunk = (t_strchunk *)ft_lstlast(strbuf->head)->content;
	if (chunk->length >= sizeof(chunk->data))
		return (TRUE);
	return (FALSE);
}

t_bool	strbuf_append(t_strbuf *strbuf, char ch)
{
	t_strchunk	*chunk;
	t_list		*new;

	if (should_new_chunk(strbuf))
	{
		chunk = new_chunk();
		new = ft_lstnew(chunk);
		if (chunk == NULL || new == NULL)
			exit_error();
		ft_lstadd_back(&strbuf->head, new);
	}
	else
		chunk = (t_strchunk *)ft_lstlast(strbuf->head)->content;
	chunk->data[chunk->length++] = ch;
	return (TRUE);
}

t_bool	strbuf_appends(t_strbuf *strbuf, const char *str)
{
	while (*str)
	{
		if (!strbuf_append(strbuf, *str))
			exit_error();
		str++;
	}
	return (TRUE);
}
