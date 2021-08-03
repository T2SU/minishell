/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 17:25:20 by smun              #+#    #+#             */
/*   Updated: 2021/08/03 17:32:17 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testlib.h"
#include "minishell.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

static void test_ft_split(void)
{
	const char *test_string = "TEST=hello\n"
								"SPL=wor ld\n"
								"ZERO=tensiya\n"
								"USER=tensiya\n"
								"PATH=/bin:/usr/bin";
	char **splitted = ft_split(test_string, '\n');
	assert(splitted != NULL);
	assert(!strcmp(splitted[0], "TEST=hello"));
	assert(!strcmp(splitted[1], "SPL=wor ld"));
	assert(!strcmp(splitted[2], "ZERO=tensiya"));
	assert(!strcmp(splitted[3], "USER=tensiya"));
	assert(!strcmp(splitted[4], "PATH=/bin:/usr/bin"));
	assert(splitted[5] == NULL);
	for (int i = 0; i < 5; i++)
		free(splitted[i]);
	free(splitted);
}

int main(int argc, char *argv[])
{
	do_test(&test_ft_split);
	print_test_result(argc, argv[0]);
	return (0);
}
