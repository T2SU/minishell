/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_angle_bracket.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 23:32:43 by smun              #+#    #+#             */
/*   Updated: 2021/08/04 14:55:17 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	parse_out_fd(t_lexer *lexer, int *pfd)
{

}

static void	parse_out_redirection(t_lexer *lexer, t_list *list)
{
	int	out_fd;

	lexer->cursor++;
	if (lexer->str[lexer->cursor] == '>')
	{
		lexer->cursor++;
		parse_out_fd(lexer, &out_fd);
		if (!add_lex(kOutRedirection, kAppend, out_fd, list))
			exit_error(get_context()->executable_name, NULL, NULL);
	}
	else
	{
		parse_out_fd(lexer, &out_fd);
		if (!add_lex(kOutRedirection, kWrite, out_fd, list))
			exit_error(get_context()->executable_name, NULL, NULL);
	}
}

static void	parse_in_redirection(t_lexer *lexer, t_list *list)
{
	lexer->cursor++;
	if (lexer->str[lexer->cursor + 1] == '<')
	{
		lexer->cursor++;
		if (!add_lex(kInRedirection, kReadTillDelim, 0, list))
			exit_error(get_context()->executable_name, NULL, NULL);
	}
	else
	{
		if (!add_lex(kInRedirection, kRead, 0, list))
			exit_error(get_context()->executable_name, NULL, NULL);
	}
}

t_bool	lexer_parse_angle_bracket(t_lexer *lexer, t_list *list)
{
	const char	c = lexer->str[lexer->cursor];

	if (c == '>')
		parse_out_redirection(lexer, list);
	else if (c == '<')
		parse_in_redirection(lexer, list);
	else
		return (FALSE);
	return (TRUE);
}
