/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 18:23:56 by smun              #+#    #+#             */
/*   Updated: 2021/08/03 17:10:41 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/_string.h"
#include <stdlib.h>

static char	**allfree(char **as, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		free(as[i++]);
	free(as);
	return (NULL);
}

static size_t	count_elems(const char *s, char c)
{
	size_t	elems_num;

	elems_num = 0;
	while (s && *s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			elems_num++;
		while (*s && *s != c)
			s++;
	}
	return (elems_num);
}

static char	*make_elem(const char *s, char c, unsigned int skip)
{
	char			*e;
	size_t			len;
	unsigned int	i;

	i = 0;
	while (i < skip)
	{
		while (*s && *s == c)
			s++;
		while (*s && *s != c)
			s++;
		i++;
	}
	len = 0;
	while (*s && *s == c)
		s++;
	while (s[len] && s[len] != c)
		len++;
	e = malloc(len + 1);
	if (e == NULL)
		return (NULL);
	ft_strlcpy(e, s, len + 1);
	return (e);
}

char	**ft_split(const char *s, char c)
{
	char			**as;
	size_t			elems_num;
	unsigned int	i;

	elems_num = count_elems(s, c);
	as = (char **)malloc(sizeof(char *) * (elems_num + 1));
	if (as == NULL)
		return (NULL);
	i = 0;
	while (i < elems_num)
	{
		as[i] = make_elem(s, c, i);
		if (as[i] == NULL)
			return (allfree(as, i));
		i++;
	}
	as[elems_num] = NULL;
	return (as);
}
