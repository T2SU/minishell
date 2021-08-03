/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:57:44 by smun              #+#    #+#             */
/*   Updated: 2021/08/03 14:11:36 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

typedef struct s_list
{
	struct s_elem	*head;
	struct s_elem	*tail;
	int				length;
}					t_list;

typedef struct s_elem
{
	void			*data;
	struct s_elem	*prev;
	struct s_elem	*next;
	void			(*destructor)(void *);
}					t_elem;

void	list_free(t_list *list);
t_elem	*list_add(t_list *list, void *data, void(*destructor)(void *));
t_elem	*list_get(t_list *list, int index);
t_elem	*list_remove(t_list *list, int index);
int		list_remove_if(t_list *list, void *data);

#endif
