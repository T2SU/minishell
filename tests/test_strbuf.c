/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strbuf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:20:08 by smun              #+#    #+#             */
/*   Updated: 2021/08/04 16:20:37 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testlib.h"
#include "minishell.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

static void	test_strbuf1(void)
{
	t_strbuf	strbuf;
	const char	*str = "Hello World!!";
	const int	len = strlen(str);
	char		*buffer;

	ft_memset(&strbuf, 0, sizeof(t_strbuf));
	for (int i = 0; i < len; i++)
		assert(strbuf_append(&strbuf, str[i]));
	buffer = strbuf_get(&strbuf, TRUE);
	assert(!strcmp(buffer, str));
}

int		main(int argc, char *argv[])
{
	do_test(&test_strbuf1);
	print_test_result(argc, argv[0]);
	return (0);
}
