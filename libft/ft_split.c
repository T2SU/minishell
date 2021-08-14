/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 21:05:16 by hkim              #+#    #+#             */
/*   Updated: 2021/01/04 17:03:50 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_malloc_err(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = 0;
		i++;
	}
	free(tab);
	return (0);
}

static int	ft_wordcount(char const *s, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c)
			cnt++;
		i++;
	}
	if (i > 0 && s[i - 1] != c)
		cnt++;
	return (cnt);
}

static char	*ft_splitsave(char const *s, int i, int len, char *tab)
{
	int	k;

	k = 0;
	while (len)
		tab[k++] = s[i - len--];
	tab[k] = '\0';
	return (tab);
}

static char	**ft_splitcut(char const *s, char c, char **tab)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = 0;
	while (s[i] && j < ft_wordcount(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			len++;
		}
		tab[j] = malloc(sizeof(char) * (len + 1));
		if (!tab)
			return (ft_malloc_err(tab));
		ft_splitsave(s, i, len, tab[j]);
		len = 0;
		j++;
	}
	tab[j] = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (0);
	tab = malloc(sizeof(char *) * ((ft_wordcount(s, c) + 1)));
	if (!tab)
		return (0);
	ft_splitcut(s, c, tab);
	return (tab);
}
