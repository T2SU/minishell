/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_memory_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 21:32:40 by smun              #+#    #+#             */
/*   Updated: 2021/09/19 01:49:52 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*safe_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (ret == NULL)
		exit_error();
	return (ret);
}

char	*safe_strdup(char *str)
{
	char	*ret;

	ret = ft_strdup(str);
	if (ret == NULL)
		exit_error();
	return (ret);
}
