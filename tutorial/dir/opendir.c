/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opendir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 19:39:32 by smun              #+#    #+#             */
/*   Updated: 2021/08/10 20:13:14 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int error(void)
{
	perror("Error");
	return EXIT_FAILURE;
}

int main(void)
{
	DIR *dir = opendir(".");
	if (dir == NULL)
		return error();
	struct dirent* dire;
	while (1)
	{
		dire = readdir(dir);
		if (dire == NULL)
			break ;
		printf("[%3lld] %32s reclen=%d type=%d\n",
			dire->d_ino, dire->d_name, dire->d_reclen, dire->d_type);
	}
	closedir(dir);
	return 0;
}
