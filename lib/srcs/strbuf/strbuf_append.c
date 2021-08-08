/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strbuf_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:54:48 by smun              #+#    #+#             */
/*   Updated: 2021/08/08 23:44:41 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strbuf.h"
#include "ft_memory.h"
#include "ft_bool.h"
#include <stdlib.h>

static t_strchunk *new_chunk(void)
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

	if (strbuf->list.length == 0)
		return (TRUE);
	chunk = (t_strchunk *)strbuf->list.tail->data;
	if (chunk->length >= sizeof(chunk->data))
		return (TRUE);
	return (FALSE);
}

t_bool	strbuf_append(t_strbuf *strbuf, char ch)
{
	t_strchunk	*chunk;

	if (should_new_chunk(strbuf))
	{
		chunk = new_chunk();
		if (!list_add(&strbuf->list, chunk, &free))
			return (FALSE);
	}
	else
		chunk = (t_strchunk *)strbuf->list.tail->data;
	chunk->data[chunk->length++] = ch;
	return (TRUE);
}
