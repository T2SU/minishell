/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 02:20:15 by hkim              #+#    #+#             */
/*   Updated: 2021/01/02 14:37:27 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dlen;
	size_t	slen;

	i = 0;
	dlen = 0;
	slen = 0;
	while (*dst)
	{
		dst++;
		dlen++;
	}
	while (src[slen] != '\0')
		slen++;
	if (dstsize != 0 && dstsize > dlen)
	{
		while (i++ < (dstsize - dlen - 1) && *src)
			*dst++ = *src++;
	}
	*dst = '\0';
	if (dstsize < dlen)
		return (slen + dstsize);
	else
		return (slen + dlen);
}
