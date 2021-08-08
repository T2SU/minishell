/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 15:12:19 by smun              #+#    #+#             */
/*   Updated: 2021/08/08 22:13:18 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <stddef.h>

t_elem	*list_get(t_list *list, int index)
{
	t_elem	*cur;
	int		i;

	if (index < 0 || index >= list->length)
		return (NULL);
	if ((list->length >> 1) > index)
	{
		cur = list->head;
		i = -1;
		while (++i < index)
			cur = cur->next;
		return (cur);
	}
	else
	{
		cur = list->tail;
		i = list->length;
		while (--i > index)
			cur = cur->prev;
		return (cur);
	}
}
