/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 14:01:01 by smun              #+#    #+#             */
/*   Updated: 2021/08/03 14:36:57 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "container/list.h"
#include "libft/libft.h"
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

t_elem	*list_add(t_list *list, void *data, void(*destructor)(void *))
{
	t_elem	*elem;

	elem = malloc(sizeof(t_elem));
	if (elem == NULL)
		return (NULL);
	ft_memset(elem, 0, sizeof(t_elem));
	elem->data = data;
	elem->destructor = destructor;
	if (list->tail)
	{
		list->tail->next = elem;
		elem->prev = list->tail;	
	}
	list->tail = elem;
	if (list->head == NULL)
		list->head = elem;
	return (elem);
}

t_elem	*list_get(t_list *list, int index)
{
	(void)list;
	(void)index;
	return (NULL);
}

t_elem	*list_remove(t_list *list, int index)
{
	(void)list;
	(void)index;
	return (NULL);
}

int	list_remove_if(t_list *list, void *data)
{
	(void)list;
	(void)data;
	return (0);
}
