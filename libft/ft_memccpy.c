/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 20:09:56 by hkim              #+#    #+#             */
/*   Updated: 2020/12/27 00:41:58 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*chard;
	unsigned char	*chars;

	i = 0;
	chard = (unsigned char *)dst;
	chars = (unsigned char *)src;
	while (i < n)
	{
		chard[i] = chars[i];
		if (chars[i] == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (0);
}
