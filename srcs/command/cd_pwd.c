/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 23:05:48 by hkim              #+#    #+#             */
/*   Updated: 2021/09/17 19:30:16 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_pwd(t_dict *dict, char *path)
{
	char	*pwd;

	pwd = dict_get(dict, "PWD");
	if (pwd)
		dict_put(dict, "OLDPWD", pwd, 1);
	else
		dict_del(dict, "OLDPWD");
	getcwd(path, PATH_MAX);
	dict_put(dict, "PWD", path, 1);
	return (EXIT_SUCCESS);
}

int	command_run_cd(int argc, char *argv[], t_dict *dict)
{
	char	*home;
	char	path[PATH_MAX];

	getcwd(path, PATH_MAX);
	if (argc == 1)
	{
		home = dict_get(dict, "HOME");
		if (chdir(home) != -1)
			return (change_pwd(dict, path));
		raise_system_error(argv[0]);
	}
	else
	{
		if (chdir(argv[1]) != -1)
			return (change_pwd(dict, path));
		raise_system_arg_error(argv[0], argv[1]);
	}
	return (EXIT_FAILURE);
}

int	command_run_pwd(int argc, char *argv[], t_dict *dict)
{
	char	path[PATH_MAX];

	(void)argc;
	(void)argv;
	(void)dict;
	getcwd(path, PATH_MAX);
	printf("%s\n", path);
	return (EXIT_SUCCESS);
}
