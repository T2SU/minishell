/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strbuf_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:55:07 by smun              #+#    #+#             */
/*   Updated: 2021/08/04 16:15:25 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "container/_container_strbuf.h"
#include "libft/_libft_memory.h"
#include "libft/_libft_string.h"
#include "ft_bool.h"
#include <stdlib.h>

static size_t	get_total_length(t_strbuf *strbuf)
{
	size_t		len;
	t_elem		*elem;
	t_strchunk	*chunk;

	len = 0;
	elem = strbuf->list.head;
	while (elem != NULL)
	{
		chunk = (t_strchunk *)elem->data;
		len += chunk->length;
		elem = elem->next;
	}
	return (len);
}

static void	copy_chunks_into_buffer(t_strbuf *strbuf, char *buffer)
{
	t_elem		*elem;
	t_strchunk	*chunk;
	int			i;

	i = 0;
	elem = strbuf->list.head;
	while (elem != NULL)
	{
		chunk = (t_strchunk *)elem->data;
		ft_memcpy(&buffer[i], chunk->data, chunk->length);
		i += chunk->length;
		elem = elem->next;
	}
	buffer[i] = '\0';
}

char	*strbuf_get(t_strbuf *strbuf, t_bool free_strbuf_after_get)
{
	const size_t	len = get_total_length(strbuf);
	char			*buffer;

	buffer = malloc(len + 1);
	if (buffer == NULL)
		return (NULL);
	copy_chunks_into_buffer(strbuf, buffer);
	if (free_strbuf_after_get)
		list_free(&strbuf->list);
	return (buffer);
}
