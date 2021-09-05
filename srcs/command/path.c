/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:51:17 by hkim              #+#    #+#             */
/*   Updated: 2021/09/05 17:10:14 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "dirent.h"
// #define _GNU_SOURCE // Makefile에 정의 시키는 것으로 이동.

static t_bool	find_file(struct dirent *info, const char *cmd, char **path)
{
	char	*tmp;

	if (!ft_strncmp(info->d_name, cmd, ft_strlen(cmd) + 1)
		&& info->d_type != DT_DIR)
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

	if (!is_command(cmd) || is_builtin(cmd))
		return (NULL);
	path = dict_get(dict, "PATH");
	if (!path)
		return (NULL);
	path_arr = ft_split(path, ':');
	new_cmd = ft_strdup(search_dir(path_arr, cmd));
	free_char_arrays(path_arr);
	return (new_cmd);
}

char	**replace_first(int	argc, char **argv, const char *new_cmd)
{
	char	**new_argv;
	int		i;

	new_argv = safe_malloc((argc + 1) * sizeof(char *));
	new_argv[argc] = NULL;
	new_argv[0] = ft_strdup(new_cmd);
	i = 1;
	while (argv[i])
	{
		new_argv[i] = ft_strdup(argv[i]);
		i++;
	}
	return (new_argv);
}
