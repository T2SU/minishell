/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 01:21:20 by hkim              #+#    #+#             */
/*   Updated: 2021/08/21 00:25:07 by hkim             ###   ########.fr       */
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
char		*dict_get(t_dict *dict, char *key);
void		dict_update(t_dict *dict, char *key, char *value);
t_bool		dict_put(t_dict *dict, char *key, char *value);
t_bool		dict_del(t_dict *dict, char *key);
void		dict_free(t_dict *dict);
void		print_lst(void *content);
t_bool		run_env(t_dict *dict);
void		run_unset(t_dict *dict, t_list *args);
void		print_export(void *content);
t_bool		run_export(t_dict *dict, t_list *args);

#endif
