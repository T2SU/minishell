/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 15:46:26 by smun              #+#    #+#             */
/*   Updated: 2021/08/15 16:26:22 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <libft.h>
# include <stdlib.h>
# include <stddef.h>
# define TRUE 1
# define FALSE 0

typedef int	t_bool;

typedef struct s_strbuf
{
	t_list	*head;
}	t_strbuf;

typedef struct s_strchunk
{
	size_t	length;
	char	data[32];
}	t_strchunk;

t_bool	strbuf_append(t_strbuf *strbuf, char ch);
t_bool	strbuf_appends(t_strbuf *strbuf, const char *str);
char	*strbuf_get(t_strbuf *strbuf, t_bool free_strbuf_after_get);
size_t	strbuf_length(t_strbuf *strbuf);

#endif
