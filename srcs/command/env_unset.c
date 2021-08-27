/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 23:33:15 by hkim              #+#    #+#             */
/*   Updated: 2021/08/27 23:38:20 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_lst(void *content)
{
	t_pair	*tmp;

	tmp = (t_pair *)content;
	if (tmp->equal)
		printf("%s=%s\n", tmp->key, tmp->value);
}

int	command_run_env(int argc, char *argv[], t_dict *dict)
{
	(void)argc;
	(void)argv;
	ft_lstiter(dict->head, &print_lst);
	return (EXIT_SUCCESS);
}

int	command_run_unset(int argc, char *argv[], t_dict *dict)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		dict_del(dict, argv[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
