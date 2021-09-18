/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basename_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 21:23:07 by smun              #+#    #+#             */
/*   Updated: 2021/09/19 01:50:20 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_basename(char *path)
{
	char	*start;

	start = ft_strrchr(path, '/');
	if (start == NULL)
		return (path);
	return (start + 1);
}
