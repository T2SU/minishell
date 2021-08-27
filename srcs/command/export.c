/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 23:32:31 by hkim              #+#    #+#             */
/*   Updated: 2021/08/27 23:52:04 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_export_with_args(int argc, char *argv[], t_dict *dict)
{
	char	*key;
	char	*value;
	int		idx;
	int		i;

	i = 0;
	while (++i < argc)
	{
		idx = find_equal(argv[i]);
		if (idx == -1)
		{
			key = ft_strdup(argv[i]);
			value = ft_strdup("");
			dict_put(dict, key, value, 0);
		}
		else
		{
			key = ft_substr(argv[i], 0, idx);
			value = ft_substr(argv[i], idx + 1, ft_strlen(argv[i]) - idx);
			dict_put(dict, key, value, 1);
		}
		free(key);
		free(value);
	}
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
	}
	else
		run_export_with_args(argc, argv, dict);
	return (EXIT_SUCCESS);
}
