/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testdictlib.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 22:41:18 by smun              #+#    #+#             */
/*   Updated: 2021/08/21 22:43:44 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testlib.h"
#include "functions.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

t_bool	assert_leaks(void)
{
	char	buffer[260];

	buffer[0] = 0;
	sprintf(buffer, "leaks %d | grep \"ROOT LEAK\"", getpid());
	if (EXIT_SUCCESS == system(buffer))
	{
		dprintf(STDERR_FILENO, "memory leak occured.\n");
		return (FALSE);
	}
	return (TRUE);
}

t_bool	assert_dictpair(t_dict *dict, int size, ...)
{
	va_list	ap;
	t_bool	ret;
	t_list	*lst;
	t_pair	*pair;
	char	*exstr;

	if (ft_lstsize(dict->head) != size)
	{
		dprintf(STDERR_FILENO, "not equal elements count. expected: %d (your:%d)\n", size, ft_lstsize(dict->head));
		return (FALSE);
	}
	va_start(ap, size);
	ret = TRUE;
	lst = dict->head;
	while (lst != NULL)
	{
		pair = lst->content;
		exstr = va_arg(ap, char*);
		if (strcmp(pair->key, exstr))
		{
			dprintf(STDERR_FILENO, "failed validate pair key. expected: {%s} (your:{%s})\n", exstr, pair->key);
			ret = FALSE;
			break;
		}
		exstr = va_arg(ap, char*);
		if (strcmp(pair->value, exstr))
		{
			dprintf(STDERR_FILENO, "failed validate pair value. expected: {%s} (your:{%s})\n", exstr, pair->key);
			ret = FALSE;
			break;
		}
		lst = lst->next;
	}
	va_end(ap);
	return (ret);
}
