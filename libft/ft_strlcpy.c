/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 21:45:45 by hkim              #+#    #+#             */
/*   Updated: 2020/12/31 11:29:38 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	int		slen;

	slen = 0;
	if (dst == 0 || src == 0)
		return (0);
	while (src[slen] != '\0')
		slen++;
	i = 0;
	if (dstsize != 0)
	{
		while (i < dstsize - 1 && *src)
		{
			*dst = *src;
			dst++;
			src++;
			i++;
		}
		*dst = '\0';
	}
	return (slen);
}
