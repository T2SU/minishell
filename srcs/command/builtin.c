/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 20:49:54 by hkim              #+#    #+#             */
/*   Updated: 2021/09/11 22:24:08 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	lower_and_cmp(char *s1, char *s2)
{
	t_bool	ret;
	int		i;

	i = 0;
	ret = TRUE;
	while (s1[i] && s2[i])
	{
		if (s1[i] >= 'A' && s1[i] <= 'Z')
			s1[i] += 32;
		if (s2[i] >= 'A' && s2[i] <= 'Z')
			s2[i] += 32;
		if (s1[i] != s2[i])
		{
			ret = FALSE;
			break ;
		}
		i++;
	}
	free(s1);
	free(s2);
	return (ret);
}

static t_bool	is_same_word(const char *str1, const char *str2)
{
	t_bool	ret;
	char	*s1;
	char	*s2;

	if (ft_strlen(str1) != ft_strlen(str2))
		return (FALSE);
	s1 = malloc(sizeof(char) * (ft_strlen(str1) + 1));
	if (!s1)
		exit_error();
	s2 = malloc(sizeof(char) * (ft_strlen(str2) + 1));
	if (!s2)
		exit_error();
	ft_strlcpy(s1, str1, ft_strlen(str1) + 1);
	ft_strlcpy(s2, str2, ft_strlen(str2) + 1);
	ret = lower_and_cmp(s1, s2);
	return (ret);
}

t_bool	is_command(const char *cmd)
{
	if (ft_strchr(cmd, '/'))
		return (FALSE);
	return (TRUE);
}

t_bool	is_builtin(const char *cmd)
{
	if (is_same_word(cmd, "echo"))
		return (TRUE);
	if (!is_same_word(cmd, "cd"))
		return (TRUE);
	if (is_same_word(cmd, "pwd"))
		return (TRUE);
	if (!ft_strncmp(cmd, "export", 7))
		return (TRUE);
	if (is_same_word(cmd, "env"))
		return (TRUE);
	if (!ft_strncmp(cmd, "unset", 6))
		return (TRUE);
	if (!ft_strncmp(cmd, "exit", 5))
		return (TRUE);
	return (FALSE);
}

int	command_run_builtin(int argc, char *argv[], t_dict *dict)
{
	int	status;

	status = 0177;
	if (argc <= 0)
		return (status);
	if (is_same_word(argv[0], "echo"))
		status = command_run_echo(argc, argv, dict);
	else if (!ft_strncmp(argv[0], "cd", 3))
		status = command_run_cd(argc, argv, dict);
	else if (is_same_word(argv[0], "pwd"))
		status = command_run_pwd(argc, argv, dict);
	else if (!ft_strncmp(argv[0], "export", 7))
		status = command_run_export(argc, argv, dict);
	else if (is_same_word(argv[0], "env"))
		status = command_run_env(argc, argv, dict);
	else if (!ft_strncmp(argv[0], "unset", 6))
		status = command_run_unset(argc, argv, dict);
	else if (!ft_strncmp(argv[0], "exit", 5))
		status = command_run_exit(argc, argv, dict);
	else
		raise_error(argv[0], "command not found");
	if (status != 0177)
		status = context_exitcode(status, 0);
	return (status);
}
