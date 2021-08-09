/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:54:31 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 16:17:12 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <list.h>
# include <strbuf.h>
# include <ft_memory.h>
# include <ft_string.h>
# include <ft_error.h>
# include <ft_bool.h>
# include "lex.h"
# include "syntax.h"

typedef struct	s_context
{
	char		*executable_name;
	char		*prompt;
	const char	*error;
	char		*desc;
}				t_context;

t_context	*get_context();
void		context_init(int argc, char *argv[], char *envp[]);
void		*raise_error(const char *error, char *desc);

#endif
