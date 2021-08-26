/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 00:51:17 by hkim              #+#    #+#             */
/*   Updated: 2021/08/25 10:36:44 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	lower_and_cmp(char *s1, char *s2)
{
	t_bool	ret;
	int		i;

	i = 0;
	ret = TRUE;
	while (s1[i] && s2[i])
	{
		if (s1[i] >= 'A' && s1[i] <= 'Z')
			s1[i] += 32;
		if (s2[i] >= 'A' && s2[i] <= 'Z')
			s2[i] += 32;
		if (s1[i] != s2[i])
		{
			ret = FALSE;
			break ;
		}
		i++;
	}
	free(s1);
	free(s2);
	return (ret);
}

t_bool	is_same_word(char *str1, char *str2)
{
	t_bool	ret;
	char	*s1;
	char	*s2;

	if (ft_strlen(str1) != ft_strlen(str2))
		return (FALSE);
	s1 = malloc(sizeof(char) * ft_strlen(str1));
	if (!s1)
		exit(1); // error
	s2 = malloc(sizeof(char) * ft_strlen(str2));
	if (!s2)
		exit(1); // error
	ft_strlcpy(s1, str1, ft_strlen(str1));
	ft_strlcpy(s2, str2, ft_strlen(str2));
	ret = lower_and_cmp(s1, s2);
	return (ret);
}

int	is_n_option(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((i == 0 && str[i] != '-') || (i != 0 && str[i] != 'n'))
			return (0);
		i++;
	}
	return (1);
}

void	run_echo(t_list *args)
{
	int		n_flag;
	char	*first;

	n_flag = 0;
	if (args)
	{
		first = (char *)args->content;
		if (is_n_option(first))
		{
			n_flag = 1;
			args = args->next;
		}
	}
	while (args)
	{
		printf("%s", (char *)args->content);
		args = args->next;
		if (args)
			printf(" ");
	}
	if (!n_flag)
		printf("\n");
}
