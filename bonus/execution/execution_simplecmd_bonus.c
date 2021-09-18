/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_simplecmd_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 16:21:06 by smun              #+#    #+#             */
/*   Updated: 2021/09/19 01:51:09 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>

void	free_char_arrays(char *arrays[])
{
	int		i;

	i = 0;
	if (arrays)
	{
		while (arrays[i])
			free(arrays[i++]);
		if (arrays)
			free(arrays);
	}
}

static int	command_run_external(char *path, char *argv[], char *envp[])
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (!is_exist(path))
		{
			raise_system_error(path);
			exit(127);
		}
		else if (is_dir(path))
			raise_error(path, "is a directory");
		else if (execve(path, argv, envp) == -1)
			raise_system_error(path);
		exit(126);
	}
	if (pid < 0)
		exit_error();
	waitpid(pid, &status, 0);
	if (context_is_signaled(status) && context_has_flag(kInSubShell))
		context_get()->flag |= kThrowed;
	if (!context_has_flag(kInChildProc))
		context_print_strsignal(status);
	return (status);
}

int	execution_simplecmd_run(t_simplecmd *scmd)
{
	t_input	input;
	t_dict	*dict;
	int		status;
	char	*new_cmd;
	char	*cmd;

	dict = context_get()->env;
	input.argv = parse_arguments(scmd, &input.argc);
	new_cmd = is_path_command(input.argv[0], dict);
	if (input.argc == 0)
		status = EXIT_SUCCESS;
	else if (!is_command(input.argv[0]) || new_cmd)
	{
		input.envp = convert_to_array(dict->head, kEnvironment);
		cmd = new_cmd;
		if (!is_command(input.argv[0]))
			cmd = input.argv[0];
		status = command_run_external(cmd, input.argv, input.envp);
		free_char_arrays(input.envp);
	}
	else
		status = command_run_builtin(input.argc, input.argv, dict);
	free(new_cmd);
	free_char_arrays(input.argv);
	return (status);
}
