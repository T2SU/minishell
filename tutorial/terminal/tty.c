/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 00:37:29 by smun              #+#    #+#             */
/*   Updated: 2021/08/11 00:42:17 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int main(void)
{
	int s = ttyslot();
	printf("ttyslot=%d\n", s);
	printf("isatty(0)=%d, isatty(1)=%d, isatty(2)=%d, isatty(3)=%d, isatty(%d)=%d\n",
		isatty(0), isatty(1), isatty(2), isatty(3), s, isatty(s));
	printf("ttyname(%d)=%s\n", 0, ttyname(0));
	printf("ttyname(%d)=%s\n", 1, ttyname(1));
	printf("ttyname(%d)=%s\n", 2, ttyname(2));
	return 0;
}
