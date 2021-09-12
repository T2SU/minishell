/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 23:33:15 by hkim              #+#    #+#             */
/*   Updated: 2021/09/12 04:46:23 by hkim             ###   ########.fr       */
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

t_bool	is_valid_name(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	command_run_unset(int argc, char *argv[], t_dict *dict)
{
	int	i;
	int	ret;

	i = 1;
	ret = EXIT_SUCCESS;
	while (i < argc)
	{
		if (!is_valid_name(argv[i]))
		{
			raise_arg_err_quote(argv[0], argv[i], "not a valid identifier");
			ret = EXIT_FAILURE;
		}
		dict_del(dict, argv[i]);
		i++;
	}
	return (ret);
}
