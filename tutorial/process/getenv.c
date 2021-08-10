/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 00:04:43 by smun              #+#    #+#             */
/*   Updated: 2021/08/11 00:37:16 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc <= 1)
		return (EXIT_FAILURE);
	printf("%s=%s\n", argv[1], getenv(argv[1]));
	return (EXIT_SUCCESS);
}
