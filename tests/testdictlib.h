/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testdictlib.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 22:42:10 by smun              #+#    #+#             */
/*   Updated: 2021/08/21 22:43:49 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTDICTLIB_H
# define TESTDICTLIB_H
# include "functions.h"

t_bool	assert_dictpair(t_dict *dict, int size, ...);
t_bool	assert_leaks(void);

#endif
