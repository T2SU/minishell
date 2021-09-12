/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:13:00 by smun              #+#    #+#             */
/*   Updated: 2021/09/12 20:10:30 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_content(void *content, enum e_convert_type type)
{
	char	*ret;
	char	*temp;
	t_pair	*pair;

	if (type == kEnvironment)
	{
		pair = content;
		temp = ft_strjoin(pair->key, "=");
		if (temp == NULL)
			exit_error();
		ret = ft_strjoin(temp, pair->value);
		free(temp);
	}
	else
		ret = ft_strdup(content);
	if (ret == NULL)
		exit_error();
	return (ret);
}

char	**convert_to_array(t_list *input, enum e_convert_type type)
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
		array[i] = get_content(lst->content, type);
		if (array[i] == NULL)
			exit_error();
		i++;
		lst = lst->next;
	}
	return (array);
}

int	get_vector_size(void *vector)
{
	void	**pvector;
	int		i;

	pvector = (void **)vector;
	i = 0;
	while (pvector[i])
		i++;
	return (i);
}
