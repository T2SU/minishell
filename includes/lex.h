/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 17:37:49 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 16:17:15 by smun             ###   ########.fr       */
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


typedef struct	s_lexer
{
	const char	*str;
	int			cursor;
}				t_lexer;

void		lexer_parse_bracket(t_lexer *lexer, t_list *list);
void		lexer_parse_and(t_lexer *lexer, t_list *list);
void		lexer_parse_bar(t_lexer *lexer, t_list *list);
void		lexer_parse_angle_bracket(t_lexer *lexer, t_list *list);
void		lexer_parse_string(t_lexer *lexer, t_list *list);
void		lexer_parse_splitter(t_lexer *lexer, t_list *list);
void		lexer_parse_variable(t_lexer *lexer, t_list *list);
void		lexer_flush_identifier(t_strbuf *strbuf, t_list *list);
void		lexer_build_identifier(t_strbuf *strbuf, char ch);
void		add_lex(int type, char *data, t_list *list);
void		add_lex_string(int type, t_strbuf *strbuf, t_list *list);
void		parse_lex(const char *command, t_list *list);
const char	*get_lex_name(int type);
void		print_lexes(t_list *list);

#endif
