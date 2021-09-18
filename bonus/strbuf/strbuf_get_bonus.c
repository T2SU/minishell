/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strbuf_get_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 16:17:56 by smun              #+#    #+#             */
/*   Updated: 2021/09/19 01:51:21 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	strbuf_length(t_strbuf *strbuf)
{
	size_t		len;
	t_list		*lst;
	t_strchunk	*chunk;

	len = 0;
	lst = strbuf->head;
	while (lst != NULL)
	{
		chunk = (t_strchunk *)lst->content;
		len += chunk->length;
		lst = lst->next;
	}
	return (len);
}

static void	copy_chunks_into_buffer(t_strbuf *strbuf, char *buffer)
{
	t_list		*lst;
	t_strchunk	*chunk;
	int			i;

	i = 0;
	lst = strbuf->head;
	while (lst != NULL)
	{
		chunk = (t_strchunk *)lst->content;
		ft_memcpy(&buffer[i], chunk->data, chunk->length);
		i += chunk->length;
		lst = lst->next;
	}
	buffer[i] = '\0';
}

char	*strbuf_get(t_strbuf *strbuf)
{
	const size_t	len = strbuf_length(strbuf);
	char			*buffer;

	buffer = malloc(len + 1);
	if (buffer == NULL)
		exit_error();
	copy_chunks_into_buffer(strbuf, buffer);
	ft_lstclear(&strbuf->head, &free);
	strbuf->flag = 0;
	return (buffer);
}
