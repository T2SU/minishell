/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 17:04:03 by smun              #+#    #+#             */
/*   Updated: 2021/08/31 17:18:24 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strlen_max(char *s1, char *s2)
{
	int	len[2];
	int	max;

	len[0] = ft_strlen(s1);
	len[1] = ft_strlen(s2);
	max = len[0];
	if (len[1] > len[0])
		max = len[1];
	return (max);
}

static t_bool	is_needed_to_swap(t_list *lst, enum e_order order)
{
	const int	len = ft_strlen_max(lst->content, lst->next->content);
	int			cmp;

	cmp = ft_strncmp(lst->content, lst->next->content, len + 1);
	if (order == kDescending)
		return (cmp < 0);
	return (cmp > 0);
}

static void	do_swap(t_list *lst)
{
	t_list	*temp;

	temp = lst->content;
	lst->content = lst->next->content;
	lst->next->content = temp;
}

void	ft_lstsort(t_list *input, enum e_order order)
{
	int		len;
	int		i;
	int		j;
	t_list	*lst;

	lst = input;
	len = ft_lstsize(lst);
	i = -1;
	while (++i < len)
	{
		j = 0;
		while (++j < len - i)
		{
			if (is_needed_to_swap(lst, order))
				do_swap(lst);
			lst = lst->next;
		}
		lst = input;
	}
}
