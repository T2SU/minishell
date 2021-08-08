/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 17:37:49 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 01:02:21 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_H
# define LEX_H

/*
** kGreater         >
** kDoubleGreater   >>
** kLesser          <
** kDoubleLesser    <<
** kDollar          $
** kAmpersand       &
** kDoubleAmpersand &&
** kBar             |
** kDoubleBar       ||
** kBackslash       \
** kOpenBracket     (
** kCloseBracket    )
** kString          "", ``, ''
** kSplitter        \s, \t
** kIdentifier
*/

enum	e_lex
{
	kGreater,
	kDoubleGreater,
	kLesser,
	kDoubleLesser,
	kInnerDollar,
	kOuterDollar,
	kAmpersand,
	kDoubleAmpersand,
	kBar,
	kDoubleBar,
	kBackslash,
	kOpenBracket,
	kCloseBracket,
	kString,
	kSplitter,
	kIdentifier,
	kLexNum
};

enum	e_open
{
	kOpen,
	kClose
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
	char		*data;
}				t_lex;

#endif
