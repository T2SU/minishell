/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 17:37:49 by smun              #+#    #+#             */
/*   Updated: 2021/08/03 18:35:58 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_H
# define LEX_H

enum	e_lex
{
	kRedirection,
	kPipe,
	kParenthesis,
	kOperator,
	kIdentifier,
	kString,
	kSplitter
};

enum	e_direction
{
	kIn,
	kOut
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
	kAppend
};

typedef struct s_lex
{
	int			type;
	union		u_data
	{
		struct s_redirection
		{
			int	mode;
		}	redirection;
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
