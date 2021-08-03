/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _string.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 16:56:43 by smun              #+#    #+#             */
/*   Updated: 2021/08/03 17:02:47 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _STRING_H
# define _STRING_H
# include <stddef.h>

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif
