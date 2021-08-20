/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 01:21:20 by hkim              #+#    #+#             */
/*   Updated: 2021/08/19 18:41:00 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# define TRUE 1
# define FALSE 0

typedef int	t_bool;

typedef struct s_dict
{
	t_list	*head;
}	t_dict;

typedef struct s_pair
{
	char	*key;
	char	*value;
}	t_pair;

t_dict		*make_dict(char **envp);
t_bool		dict_put(t_dict *dict, char *key, char *value);
char		*dict_get(t_dict *dict, char *key);
t_bool		dict_del(t_dict *dict, char *key);
void		dict_free(t_dict *dict);
void		print_lst(void *content);
t_bool		run_env(t_dict *dict);
t_bool		run_unset(t_dict *dict, t_list *args);
void		print_export(void *content);

#endif
