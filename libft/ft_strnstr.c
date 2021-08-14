/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 21:35:00 by hkim              #+#    #+#             */
/*   Updated: 2020/12/26 16:31:52 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	str = (char *)haystack;
	if (*needle == '\0')
		return (str);
	while (str[i] != '\0' && i < len)
	{
		j = 0;
		if (str[i] == *needle)
		{
			while (needle[j] && str[i] && i + j < len)
			{
				if (str[i + j] != needle[j])
					break ;
				j++;
			}
			if (needle[j] == '\0')
				return (str + i);
		}
		i++;
	}
	return (0);
}
