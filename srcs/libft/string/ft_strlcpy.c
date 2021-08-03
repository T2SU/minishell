/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 22:51:57 by smun              #+#    #+#             */
/*   Updated: 2021/08/03 17:11:06 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/_string.h"
#include "libft/_memory.h"

static size_t	truncate_len(size_t slen, size_t dstsize)
{
	if (slen >= dstsize)
		return (dstsize - 1);
	return (slen);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	slen;
	size_t	cpylen;

	slen = ft_strlen(src);
	if (dstsize > 0)
	{
		cpylen = truncate_len(slen, dstsize);
		ft_memcpy(dst, src, cpylen);
		if (dst)
			dst[cpylen] = '\0';
	}
	return (slen);
}
