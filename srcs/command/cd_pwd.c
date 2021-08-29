/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 23:05:48 by hkim              #+#    #+#             */
/*   Updated: 2021/08/29 18:18:44 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_run_cd(int argc, char *argv[], t_dict *dict)
{
	char	*home;

	if (argc > 2)
		printf("cd: too many arguments\n");
	else if (argc == 2)
	{
		if (chdir(argv[1]) == -1)
			raise_system_arg_error(argv[0], argv[1]);
	}
	else if (argc == 1)
	{
		home = dict_get(dict, "HOME");
		if (chdir(home) == -1)
			raise_system_error(argv[0]);
	}
	return (EXIT_SUCCESS);
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
