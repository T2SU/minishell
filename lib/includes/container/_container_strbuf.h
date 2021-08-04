/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _container_strbuf.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:49:26 by smun              #+#    #+#             */
/*   Updated: 2021/08/04 16:19:38 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CONTAINER_STRBUF_H
# define _CONTAINER_STRBUF_H
# include "_container_list.h"
# include "ft_bool.h"
# include <stddef.h>

typedef struct s_strbuf
{
	t_list	list;
}			t_strbuf;

typedef struct s_strchunk
{
	size_t	length;
	char	data[32];
}			t_strchunk;

t_bool	strbuf_append(t_strbuf *strbuf, char ch);
char	*strbuf_get(t_strbuf *strbuf, t_bool free_strbuf_after_get);

#endif
