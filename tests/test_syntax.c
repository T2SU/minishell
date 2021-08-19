/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 18:03:24 by smun              #+#    #+#             */
/*   Updated: 2021/08/19 21:29:49 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testlib.h"
#include "minishell.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static void	test_simple2(void)
{
	t_syntax	*syntax;

	// tokenizer.str = "(ER >> dd << dd g f | cat < b < gogo $US>>ER| A$B\"C\" > dd && (true || false | (go $A << gos)))|cat 43a sda<<dso>das ddd g\"$'sd\"s'";
	//parse(&syntax, ft_strdup("(ER >> dd << dd g f | cat < b < gogo $US>>ER| A$B\"C\" > dd && (true || false | (go $A << gos)))|cat 43a sda<<dso>das ddd g\"$'sd\"s'"));
	//parse(&syntax, ft_strdup("echo \"hello world\" > hello.log"));
	parse(&syntax, ft_strdup("> d"));
	dispose_syntax(syntax);
}

int		main(void)
{
	test_simple2();
	return (0);
}
