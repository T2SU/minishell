/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 15:11:27 by smun              #+#    #+#             */
/*   Updated: 2021/08/03 15:11:40 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "container/list.h"
#include "libft/libft.h"
#include <stdlib.h>

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
	list->length++;
	return (elem);
}
