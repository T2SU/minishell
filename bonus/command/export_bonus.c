/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 23:32:31 by hkim              #+#    #+#             */
/*   Updated: 2021/09/19 01:50:10 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	invalid_exit(const char *why, const char *arg)
{
	raise_arg_err_quote(why, arg, "not a valid identifier");
	return (EXIT_FAILURE);
}

static int	put_key_value(int idx, char **argv, int i, t_dict *dict)
{
	char	*key;
	char	*value;
	int		ret;

	ret = EXIT_SUCCESS;
	if (idx == -1)
	{
		key = ft_strdup(argv[i]);
		if (!is_valid_name(key))
			ret = invalid_exit(argv[0], argv[i]);
		value = ft_strdup("");
	}
	else
	{
		key = ft_substr(argv[i], 0, idx);
		value = ft_substr(argv[i], idx + 1, ft_strlen(argv[i]) - idx);
		if (!is_valid_name(key))
			ret = invalid_exit(argv[0], argv[i]);
	}
	if (ret == EXIT_SUCCESS)
		dict_put(dict, key, value, idx != -1);
	free(key);
	free(value);
	return (ret);
}

static int	run_export_with_args(int argc, char *argv[], t_dict *dict)
{
	int		ret;
	int		idx;
	int		i;

	i = 0;
	ret = EXIT_SUCCESS;
	while (++i < argc)
	{
		if (!ft_strncmp(argv[i], "=", 2))
		{
			ret = invalid_exit(argv[0], argv[i]);
			continue ;
		}
		idx = find_equal(argv[i]);
		if (put_key_value(idx, argv, i, dict) != EXIT_SUCCESS)
			ret = EXIT_FAILURE;
	}
	return (ret);
}

int	command_run_export(int argc, char *argv[], t_dict *dict)
{
	t_dict	*new_dict;

	if (dict == NULL)
		return (EXIT_FAILURE);
	if (argc < 2)
	{
		new_dict = sort_dict(dict);
		ft_lstiter(new_dict->head, &print_export);
		dict_free(new_dict);
		return (EXIT_SUCCESS);
	}
	else
		return (run_export_with_args(argc, argv, dict));
}
