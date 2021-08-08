/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:54:31 by smun              #+#    #+#             */
/*   Updated: 2021/08/08 23:59:07 by smun             ###   ########.fr       */
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
void	lexer_parse_and(t_lexer *lexer, t_list *list);
void	lexer_parse_bar(t_lexer *lexer, t_list *list);
void	lexer_parse_angle_bracket(t_lexer *lexer, t_list *list);
void	lexer_parse_string(t_lexer *lexer, t_list *list);
void	lexer_parse_splitter(t_lexer *lexer, t_list *list);
void	lexer_parse_variable(t_lexer *lexer, t_list *list);
void	lexer_flush_identifier(t_strbuf *strbuf, t_list *list);
void	lexer_build_identifier(t_strbuf *strbuf, char ch);
t_bool	add_lex(int type, char *data, t_list *list);
t_bool	add_lex_string(int type, t_strbuf *strbuf, t_list *list);
void	parse_lex(const char *command, t_list *list);
void	print_lexes(t_list *list);

#endif
