/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 00:24:41 by smun              #+#    #+#             */
/*   Updated: 2021/08/17 17:22:48 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variable(char *name)
{
	char	*ret;

	ret = ft_strdup(name);
	free(name);
	if (ret == NULL)
		exit_error();
	return (ret);
}
