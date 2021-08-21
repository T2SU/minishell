/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 18:26:01 by hkim              #+#    #+#             */
/*   Updated: 2021/08/20 23:25:31 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

void	print_export(void *content)
{
	t_pair	*tmp;
	char	*str;

	tmp = (t_pair *)content;
	printf("declare -x %s=\"", tmp->key);
	str = tmp->value;
	while (*str)
	{
		if (*str == '\\' || *str == '$')
			printf("\\");
		printf("%c", *str);
		str++;
	}
	printf("\"\n");
}

void	print_lst(void *content)
{
	t_pair	*tmp;

	tmp = (t_pair *)content;
	printf("%s=%s\n", tmp->key, tmp->value);
}

t_bool	run_env(t_dict *dict)
{
	if (dict == NULL)
		return (FALSE);
	ft_lstiter(dict->head, &print_lst);
	return (TRUE);
}

void	run_unset(t_dict *dict, t_list *args)
{
	while (args)
	{
		dict_del(dict, (char *)args->content);
		args = args->next;
	}
}
