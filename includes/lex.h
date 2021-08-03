/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 17:37:49 by smun              #+#    #+#             */
/*   Updated: 2021/08/04 00:52:55 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_H
# define LEX_H

enum	e_lex
{
	kInRedirection,
	kOutRedirection,
	kPipe,
	kParenthesis,
	kOperator,
	kIdentifier,
	kString,
	kSplitter
};

enum	e_open
{
	kOpen,
	kClose
};

enum	e_operator
{
	kAnd,
	kOr
};

enum	e_mode
{
	kWrite,
	kAppend,
	kRead,
	kReadTillDelim
};

typedef struct s_lex
{
	int			type;
	union		u_data
	{
		struct s_in
		{
			int	mode;
		}	in;
		struct s_out
		{
			int	mode;
			int	fd;
		}	out;
		struct s_parenthesis
		{
			int	data;
		}	parenthesis;
		struct s_operator
		{
			int	type;
		}	op;
		struct s_identifier
		{
			const char	*data;
		}	identifier;
	}			data;
}				t_lex;

#endif
