/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _libft_string.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 16:56:43 by smun              #+#    #+#             */
/*   Updated: 2021/08/04 15:27:16 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIBFT_STRING_H
# define _LIBFT_STRING_H
# include <stddef.h>
# include "ft_bool.h"

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(const char *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
t_bool	ft_atoi_strict(const char *s, int *pvalue);
char	*ft_strchr(const char *s, int c);

#endif
