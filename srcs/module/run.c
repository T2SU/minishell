/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 18:42:04 by hkim              #+#    #+#             */
/*   Updated: 2021/08/25 10:40:25 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_cd(t_list *args, char *home)
{
	if (ft_lstsize(args) > 1)
		printf("cd: too many arguments\n");
	else if (ft_lstsize(args) == 1)
	{
		if (chdir((char *)args->content) == -1)
			printf("cd: %s: %s\n", (char *)args->content, strerror(errno));
	}
	else if (ft_lstsize(args) == 0)
	{
		if (chdir(home) == -1)
			printf("cd: %s\n", strerror(errno));
	}
}

void	run_pwd(void)
{
	char	path[PATH_MAX];

	getcwd(path, PATH_MAX);
	printf("%s\n", path);
}

int	is_str_num(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			res = 0;
			break ;
		}
		i++;
	}
	return (res);
}

void	run_exit(t_list *args)
{
	printf("exit\n");
	if (ft_lstsize(args) == 0)
		exit(0);
	else if (!is_str_num(args->content))
	{
		printf("exit: %s: numeric argument required\n", (char *)args->content);
		exit(1);
	}
	else if (ft_lstsize(args) > 1)
		printf("exit: too many arguments\n");
	else
		exit(ft_atoi(args->content));
}
