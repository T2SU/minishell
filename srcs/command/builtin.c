/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 20:49:54 by hkim              #+#    #+#             */
/*   Updated: 2021/08/27 23:35:44 by hkim             ###   ########.fr       */
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
	s1 = malloc(sizeof(char) * ft_strlen(str1));
	if (!s1)
		exit(1); // error
	s2 = malloc(sizeof(char) * ft_strlen(str2));
	if (!s2)
		exit(1); // error
	ft_strlcpy(s1, str1, ft_strlen(str1));
	ft_strlcpy(s2, str2, ft_strlen(str2));
	ret = lower_and_cmp(s1, s2);
	return (ret);
}

t_bool	command_is_builtin(const char *cmd)
{
	if (is_same_word(cmd, "echo"))
		return (TRUE);
	if (!ft_strncmp(cmd, "cd", 2))
		return (TRUE);
	if (is_same_word(cmd, "pwd"))
		return (TRUE);
	if (!ft_strncmp(cmd, "export", 6))
		return (TRUE);
	if (is_same_word(cmd, "env"))
		return (TRUE);
	if (!ft_strncmp(cmd, "unset", 5))
		return (TRUE);
	if (!ft_strncmp(cmd, "exit", 4))
		return (TRUE);
	return (FALSE);
}

int	command_run_builtin(int argc, char *argv[], t_dict *dict)
{
	if (argc <= 0)
		return (EXIT_FAILURE);
	if (is_same_word(argv[0], "echo"))
		return (command_run_echo(argc, argv, dict));
	if (!ft_strncmp(argv[0], "cd", 2))
		return (command_run_cd(argc, argv, dict));
	if (is_same_word(argv[0], "pwd"))
		return (command_run_pwd(argc, argv, dict));
	if (!ft_strncmp(argv[0], "export", 6))
		return (command_run_export(argc, argv, dict));
	if (is_same_word(argv[0], "env"))
		return (command_run_env(argc, argv, dict));
	if (!ft_strncmp(argv[0], "unset", 5))
		return (command_run_unset(argc, argv, dict));
	if (!ft_strncmp(argv[0], "exit", 4))
		return (command_run_exit(argc, argv, dict));
	raise_error(argv[0], "command not found");
	return (EXIT_FAILURE);
}
