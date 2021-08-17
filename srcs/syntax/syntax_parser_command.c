/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parser_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 23:20:53 by smun              #+#    #+#             */
/*   Updated: 2021/08/17 15:10:09 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

static void	try_parse_word(t_parser *parser, t_command *ret)
{
	t_list	*lst;
	char	*word;

	word = get_word(parser);
	if (word == NULL)
		return ;
	lst = ft_lstnew(word);
	if (lst == NULL)
		exit_error();
	ft_lstadd_back(&ret->args, lst);
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

static t_bool	try_parse_redirection(t_parser *parser, t_command *ret)
{
	t_list			*lst;
	t_redirection	*redir;
	int				type;
	char			*word;

	skip_whitespaces(parser);
	if (!is_redirection_acceptable(parser))
		return (TRUE);
	type = ((t_token *)parser->cur)->type;
	parser->cur = parser->cur->next;
	word = get_word(parser);
	if (word == NULL)
		return (FALSE);
	redir = malloc(sizeof(t_redirection));
	lst = ft_lstnew(redir);
	if (redir == NULL || lst == NULL)
		exit_error();
	determine_type(redir, type);
	ft_lstadd_back(&ret->redirs, lst);
	return (TRUE);
}

t_command	*next_command(t_parser *parser)
{
	t_command	*ret;

	ret = malloc(sizeof(t_command));
	if (ret == NULL)
		exit_error();
	ft_memset(ret, 0, sizeof(t_command));
	while (parser->cur != NULL)
	{
		try_parse_word(parser, ret);
		if (!try_parse_redirection(parser, ret))
		{
			free(ret);
			return (NULL);
		}
	}
	if (ret->args == NULL && ret->redirs == NULL)
	{
		free(ret);
		return (NULL);
	}
	return ret;
}
