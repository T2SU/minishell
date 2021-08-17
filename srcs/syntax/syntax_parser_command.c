/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parser_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 23:20:53 by smun              #+#    #+#             */
/*   Updated: 2021/08/17 18:33:27 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

static t_bool	try_parse_word(t_parser *parser, t_command *ret, int *st)
{
	t_list	*lst;
	char	*word;

	skip_whitespaces(parser);
	if (ret->args != NULL)
		if (is_acceptable(parser->cur, Token_OpenBracket))
			return (*st = CmdStatus_Error);
	word = get_word(parser);
	if (word == NULL)
		return (*st = CmdStatus_NotFound);
	lst = ft_lstnew(word);
	if (lst == NULL)
		exit_error();
	ft_lstadd_back(&ret->args, lst);
	return (*st = CmdStatus_Success);
}

static t_bool	is_redirection_acceptable(t_parser *parser)
{
	if (is_acceptable(parser->cur, Token_Write))
		return (TRUE);
	if (is_acceptable(parser->cur, Token_Append))
		return (TRUE);
	if (is_acceptable(parser->cur, Token_ReadDelim))
		return (TRUE);
	if (is_acceptable(parser->cur, Token_Read))
		return (TRUE);
	return (FALSE);
}

static void	determine_type(t_redirection *r, int type)
{
	if (type == Token_Read)
		r->type = RedirType_Read;
	if (type == Token_Write)
		r->type = RedirType_Write;
	if (type == Token_Append)
		r->type = RedirType_Append;
	if (type == Token_ReadDelim)
		r->type = RedirType_ReadDelim;
}

static t_bool	try_parse_redir(t_parser *parser, t_command *ret, int *st)
{
	t_list			*lst;
	t_redirection	*redir;
	int				type;
	char			*word;

	skip_whitespaces(parser);
	if (!is_redirection_acceptable(parser))
		return (*st = CmdStatus_Pass);
	type = ((t_token *)parser->cur->content)->type;
	parser->cur = parser->cur->next;
	word = get_word(parser);
	if (word == NULL)
		return (*st = CmdStatus_Error);
	redir = malloc(sizeof(t_redirection));
	lst = ft_lstnew(redir);
	if (redir == NULL || lst == NULL)
		exit_error();
	redir->name = word;
	determine_type(redir, type);
	ft_lstadd_back(&ret->redirs, lst);
	return (*st = CmdStatus_Success);
}

/*
** Truth table:
**   - Failed to parse word && no redir token = break loop
**   - Failed to parse redir (yes redir token) = syntax error
**   - Nothing on parsed word or parsed redir = syntax error
*/

t_command	*next_command(t_parser *parser)
{
	int			status[2];
	t_command	*ret;

	ret = malloc(sizeof(t_command));
	if (ret == NULL)
		exit_error();
	ft_memset(ret, 0, sizeof(t_command));
	while (parser->cur != NULL)
	{
		ft_memset(status, 0, sizeof(status));
		try_parse_word(parser, ret, &status[0]);
		try_parse_redir(parser, ret, &status[1]);
		if ((status[0] | status[1]) & CmdStatus_Error)
			break ;
		if (status[0] == CmdStatus_NotFound && status[1] == CmdStatus_Pass)
			break ;
	}
	if ((ret->args == NULL && ret->redirs == NULL)
		|| (status[0] == CmdStatus_Error || status[1] == CmdStatus_Error))
	{
		free_command(ret);
		ret = NULL;
	}
	return (ret);
}
