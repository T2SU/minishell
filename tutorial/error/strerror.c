/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strerror.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 19:39:32 by smun              #+#    #+#             */
/*   Updated: 2021/08/10 22:29:11 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <string.h>

#define PRINTE(err) \
	printf("%s = %s\n", #err, strerror(err))

int main(void)
{
	PRINTE(ENOMEM);
	PRINTE(EALREADY);
	PRINTE(EBADEXEC);
	PRINTE(EINVAL);
	return 0;
}
