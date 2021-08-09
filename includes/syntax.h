/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 14:37:50 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 23:52:45 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H
# include <list.h>

enum	e_syntax
{
	Syntax_String,
	Syntax_Expression
};

enum	e_expression
{
	Expression_Read,
	Expression_ReadDelim,
	Expression_Write,
	Expression_Append,
	Expression_Pipe,
	Expression_And,
	Expression_Or,
	Expression_Command,
	Expression_SubShell,
	Expression_Num
};

typedef struct s_parser
{
	t_list		collected;
	t_strbuf	strbuf;
	t_list		*lexes;
	t_elem		*current;
}			t_parser;


/*
** - String
**   1. char *  - Raw String
**   2. $char * - Environment Variable Name
**
** - Command
**   1. <String>
**   2. <String> <String>
**   3. <String> <String> <String>
**   ...
**
** - Expression
**   1. <Expression> '<' <String>(FileName)
**   2. <Expression> '<<' <String>(EOF Token)
**   3. <Expression> '>' <String>(FileName)
**   4. <Expression> '>>' <String>(FileName)
**   5. <Expression> '|' <Expression>
**   6. <Expression> '&&' <Expression>
**   7. <Expression> '||' <Expression>
**   8. <Command>
**   9. <SubShell>
**
** - SubShell '(', ')'
**   1. <Expression>
*/

typedef struct s_expr
{
	int		type;
	union	u_exprdata
	{
		struct	s_command
		{
			t_list	list;
		}	command;
		struct	s_subshell
		{
			struct s_expr	*expr;
		}	subshell;
		struct	s_binary
		{
			void	*ahead;
			void	*behind;
		}	binary;
	}	data;
}			t_expr;

typedef struct s_syntax
{
	int		type;
	union	u_syntaxdata
	{
		struct	s_string
		{
			char	*name;
			t_bool	variable;
		}	string;
		t_expr	*expr;
	}	data;
}			t_syntax;

t_syntax	*syntax_parse(t_parser *parser);
t_expr		*parse_command(t_parser *parser);
t_expr		*get_expr(t_parser *parser, int type);
void		collect_token(t_list *collected, t_strbuf *strbuf);
t_bool		parse_variable(t_list *collected, t_list *list, t_elem *cur);
t_expr		*build_expr_command(t_parser *parser);
void		expr_free(t_expr *expr);

#endif
