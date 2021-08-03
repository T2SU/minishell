/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 23:21:00 by smun              #+#    #+#             */
/*   Updated: 2021/08/03 17:33:32 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/_libft_string.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*s;

	len = ft_strlen(s1);
	s = (char *)malloc(len + 1);
	if (s == NULL)
		return (NULL);
	ft_strlcpy(s, s1, len + 1);
	return (s);
}
