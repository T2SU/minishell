/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 13:45:34 by smun              #+#    #+#             */
/*   Updated: 2021/08/31 11:58:00 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

t_bool	is_exist(const char *path)
{
	struct stat	s;

	if (-1 == stat(path, &s))
		return (FALSE);
	return (TRUE);
}

/*
** (s.st_mode & S_IFMT) == S_IFDIR -> S_ISDIR(s.st_mode)
*/

t_bool	is_dir(const char *path)
{
	struct stat	s;

	if (-1 == stat(path, &s))
		return (TRUE);
	if ((s.st_mode & S_IFMT) == S_IFDIR)
	{
		errno = EISDIR;
		return (TRUE);
	}
	return (FALSE);
}
