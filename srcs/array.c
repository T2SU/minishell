/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:13:00 by smun              #+#    #+#             */
/*   Updated: 2021/08/31 16:50:37 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**convert_to_array(t_list *input)
{
	int		count;
	t_list	*lst;
	char	**array;
	int		i;

	count = ft_lstsize(input);
	array = safe_malloc((1 + count) * sizeof(char *));
	array[count] = NULL;
	lst = input;
	i = 0;
	while (lst != NULL)
	{
		array[i] = ft_strdup(lst->content);
		if (array[i] == NULL)
			exit_error();
		i++;
		lst = lst->next;
	}
	return (array);
}
