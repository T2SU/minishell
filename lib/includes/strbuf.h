/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strbuf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:49:26 by smun              #+#    #+#             */
/*   Updated: 2021/08/08 23:44:55 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRBUF_H
# define STRBUF_H
# include "list.h"
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
size_t	strbuf_length(t_strbuf *strbuf);

#endif
