/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:51:17 by hkim              #+#    #+#             */
/*   Updated: 2021/09/12 03:23:25 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "dirent.h"
// #define _GNU_SOURCE // Makefile에 정의 시키는 것으로 이동.

static t_bool	find_file(struct dirent *info, const char *cmd, char **path)
{
	char	*tmp;

	if (is_same_word(info->d_name, cmd) && info->d_type != DT_DIR)
	{
		tmp = *path;
		*path = ft_strjoin(*path, "/");
		free(tmp);
		tmp = *path;
		*path = ft_strjoin(*path, cmd);
		free(tmp);
		return (TRUE);
	}
	return (FALSE);
}

static char	*search_dir(char **path_arr, const char *cmd)
{
	int				i;
	DIR				*dir;
	struct dirent	*dir_info;

	i = -1;
	while (path_arr[++i])
	{
		dir = opendir(path_arr[i]);
		if (!dir)
			continue ;
		while (TRUE)
		{
			dir_info = readdir(dir);
			if (!dir_info)
				break ;
			if (find_file(dir_info, cmd, &path_arr[i]))
			{
				closedir(dir);
				return (path_arr[i]);
			}
		}
		closedir(dir);
	}
	return (NULL);
}

char	*is_path_command(const char *cmd, t_dict *dict)
{
	char	*path;
	char	**path_arr;
	char	*new_cmd;
	char	*ret;

	if (cmd == NULL || !is_command(cmd) || is_builtin(cmd))
		return (NULL);
	path = dict_get(dict, "PATH");
	if (!has_path_variable(dict))
		return (NULL);
	path_arr = ft_split(path, ':');
	new_cmd = search_dir(path_arr, cmd);
	ret = NULL;
	if (new_cmd)
		ret = ft_strdup(new_cmd);
	free_char_arrays(path_arr);
	return (ret);
}

t_bool	has_path_variable(t_dict *dict)
{
	char	*path;

	path = dict_get(dict, "PATH");
	if (path == NULL)
		return (FALSE);
	if (ft_strlen(path) == 0)
		return (FALSE);
	return (TRUE);
}
