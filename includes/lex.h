/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 17:37:49 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 14:43:12 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_H
# define LEX_H

/*
** Lex_Greater         >
** Lex_DoubleGreater   >>
** Lex_Lesser          <
** Lex_DoubleLesser    <<
** kDollar          $
** Lex_Ampersand       &
** Lex_DoubleAmpersand &&
** Lex_Bar             |
** Lex_DoubleBar       ||
** Lex_Backslash       \
** Lex_OpenBracket     (
** Lex_CloseBracket    )
** Lex_String          "", ``, ''
** Lex_Splitter        \s, \t
** Lex_Identifier
*/

enum	e_lex
{
	Lex_Greater,
	Lex_DoubleGreater,
	Lex_Lesser,
	Lex_DoubleLesser,
	Lex_InnerDollar,
	Lex_OuterDollar,
	Lex_Ampersand,
	Lex_DoubleAmpersand,
	Lex_Bar,
	Lex_DoubleBar,
	Lex_Backslash,
	Lex_OpenBracket,
	Lex_CloseBracket,
	Lex_String,
	Lex_Splitter,
	Lex_Identifier,
	Lex_Num
};

typedef struct s_lex
{
	int			type;
	char		*data;
}				t_lex;

#endif
