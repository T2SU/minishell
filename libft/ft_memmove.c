/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 20:31:44 by hkim              #+#    #+#             */
/*   Updated: 2020/12/27 00:42:57 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*d_char;
	unsigned char	*s_char;

	if (dst == src || len == 0)
		return (dst);
	d_char = (unsigned char *)dst;
	s_char = (unsigned char *)src;
	i = -1;
	if (src > dst)
	{
		while (++i < len)
			d_char[i] = s_char[i];
	}
	else
	{
		while (++i < len)
			d_char[len - i - 1] = s_char[len - i - 1];
	}
	return (dst);
}
