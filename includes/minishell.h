/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:54:31 by smun              #+#    #+#             */
/*   Updated: 2021/08/04 17:50:10 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <container/_container_list.h>
# include <container/_container_strbuf.h>
# include <libft/_libft_memory.h>
# include <libft/_libft_string.h>
# include <error/_error_handling.h>
# include <ft_bool.h>
# include "lex.h"

typedef struct	s_context
{
	char	*executable_name;
	char	*prompt;
}			t_context;

t_context	*get_context();

typedef struct	s_lexer
{
	const char	*str;
	int			cursor;
}				t_lexer;

void	lexer_parse_bracket(t_lexer *lexer, t_list *list);
t_bool	lexer_parse_and(t_lexer *lexer, t_list *list);
void	lexer_parse_bar(t_lexer *lexer, t_list *list);
void	lexer_parse_angle_bracket(t_lexer *lexer, t_list *list);
void	lexer_parse_string(t_lexer *lexer, t_list *list);
void	lexer_parse_splitter(t_lexer *lexer, t_list *list);
void	lexer_parse_variable(t_lexer *lexer, t_list *list);
void	lexer_flush_identifier(t_strbuf *strbuf, t_list *list);
void	lexer_build_identifier(t_strbuf *strbuf, char ch);
t_bool	add_lex(int type, int data, t_list *list);
t_bool	add_lex_string(int type, t_strbuf *strbuf, t_list *list);
void	parse_lex(const char *command, t_list *list);

#endif
