/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 15:12:33 by smun              #+#    #+#             */
/*   Updated: 2021/08/08 22:13:22 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <stdlib.h>

static void	remove_element(t_list *list, t_elem *elem)
{
	if (list->head == elem)
		list->head = elem->next;
	if (list->tail == elem)
		list->tail = elem->prev;
	if (elem->next)
		elem->next->prev = elem->prev;
	if (elem->prev)
		elem->prev->next = elem->next;
	if (elem->destructor)
		(elem->destructor)(elem->data);
	free(elem);
	list->length--;
}

int	list_remove(t_list *list, int index)
{
	t_elem	*elem;

	elem = list_get(list, index);
	if (elem == NULL)
		return (0);
	remove_element(list, elem);
	return (1);
}

int	list_remove_if(t_list *list, void *data)
{
	t_elem	*elem;
	t_elem	*next;
	int		count;

	count = 0;
	elem = list->head;
	while (elem != NULL)
	{
		next = elem->next;
		if (elem->data == data)
		{
			remove_element(list, elem);
			count++;
		}
		elem = next;
	}
	return (count);
}
