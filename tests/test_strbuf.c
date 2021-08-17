/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strbuf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:20:08 by smun              #+#    #+#             */
/*   Updated: 2021/08/17 18:44:42 by smun             ###   ########.fr       */
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
	buffer = strbuf_get(&strbuf);
	assert(!strcmp(buffer, str));
}

static void	test_strbuf2(void)
{
	t_strbuf	strbuf;
	char		*buffer;

	ft_memset(&strbuf, 0, sizeof(t_strbuf));
	assert(strbuf_appends(&strbuf, "Hel"));
	assert(strbuf_appends(&strbuf, ""));
	assert(strbuf_appends(&strbuf, "l"));
	assert(strbuf_appends(&strbuf, ""));
	assert(strbuf_appends(&strbuf, "o"));
	assert(strbuf_appends(&strbuf, " World!!"));
	assert(strbuf_appends(&strbuf, ""));
	buffer = strbuf_get(&strbuf);
	assert(!strcmp(buffer, "Hello World!!"));
}

int		main(int argc, char *argv[])
{
	do_test(&test_strbuf1);
	do_test(&test_strbuf2);
	print_test_result(argc, argv[0]);
	return (0);
}
