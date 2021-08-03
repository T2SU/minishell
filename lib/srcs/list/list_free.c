/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 15:11:50 by smun              #+#    #+#             */
/*   Updated: 2021/08/03 17:33:53 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "container/_container_list.h"
#include <stdlib.h>

void	list_free(t_list *list)
{
	t_elem	*cur;
	t_elem	*next;

	cur = list->head;
	while (cur != NULL)
	{
		next = cur->next;
		if (cur->destructor)
			(cur->destructor)(cur->data);
		free(cur);
		cur = next;
	}
}
