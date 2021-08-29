/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 13:45:34 by smun              #+#    #+#             */
/*   Updated: 2021/08/29 14:37:44 by smun             ###   ########.fr       */
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

t_bool	is_dir(const char *path)
{
	struct stat	s;

	if (-1 == stat(path, &s))
		return (TRUE);
	if (S_ISDIR(s.st_mode))
	{
		errno = EISDIR;
		return (TRUE);
	}
	return (FALSE);
}
