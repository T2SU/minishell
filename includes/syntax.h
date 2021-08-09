/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 14:37:50 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 16:09:09 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H
# include <list.h>

enum	e_syntax
{
	Syntax_Command,
	Syntax_Pipe,
	Syntax_Read,
	Syntax_ReadWithDelimiter,
	Syntax_Write,
	Syntax_Append,
	Syntax_SubShell,
	Syntax_And,
	Syntax_Or
};

typedef struct s_parser
{
	t_list	*lexes;
	t_elem	*current;
	t_list	collected_args;
}			t_parser;

typedef struct s_syntax
{
	int		type;
	union	u_syntaxdata
	{
		struct s_command
		{
			t_list	list;
		}	command;
		struct s_pipe
		{
			t_syntax	*ahead;
			t_syntax	*behind;
		}	pipe;
		struct s_read
		{
			t_syntax	*expr;
			char		*filename;
		}	read;
		struct s_readdelim
		{
			t_syntax	*expr;
			char		*eof;
		}	readdelim;
		struct s_write
		{
			t_syntax	*expr;
			char		*filename;
		}	write;
		struct s_append
		{
			t_syntax	*expr;
			char		*filename;
		}	append;
		struct s_subshell
		{
			t_syntax	*expr;
		}	subshell;
		struct s_and
		{
			t_syntax	*ahead;
			t_syntax	*behind;
		}	and;
		struct s_or
		{
			t_syntax	*ahead;
			t_syntax	*behind;
		}	or;
	}	data;
}			t_syntax;

void		syntax_append_argument(t_parser *parser);
t_syntax	*syntax_build_command(t_parser *parser);
t_syntax	*syntax_parse(t_parser *parser);
t_syntax	*syntax_parse_pipe(t_parser *parser);
t_syntax	*syntax_parse_read(t_parser *parser);
t_syntax	*syntax_parse_readdelim(t_parser *parser);
t_syntax	*syntax_parse_write(t_parser *parser);
t_syntax	*syntax_parse_append(t_parser *parser);
t_syntax	*syntax_parse_subshell(t_parser *parser);
t_syntax	*syntax_parse_and(t_parser *parser);
t_syntax	*syntax_parse_or(t_parser *parser);

#endif
