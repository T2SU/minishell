/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:54:31 by smun              #+#    #+#             */
/*   Updated: 2021/08/03 18:49:59 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "container/_container_list.h"
# include "libft/_libft_memory.h"
# include "libft/_libft_string.h"
# include "lex.h"
# define TRUE 1
# define FALSE 0

typedef int	t_bool;

enum	e_lexer_state
{
	kLexerNormal,
	kLexerParsingString
};

typedef struct	s_lexer
{
	const char	*str;
	int			cursor;
	int			state;
}				t_lexer;

t_bool	parse_lex(const char *command, t_list *list);

#endif
