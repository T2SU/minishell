/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc_prepare.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 14:46:55 by smun              #+#    #+#             */
/*   Updated: 2021/09/12 17:21:02 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	prepare(t_redir *redir)
{
	if (redir->type != kReadHeredoc)
		return (TRUE);
	redir->heredoc_file = execution_make_heredoc(redir);
	if (redir->heredoc_file == NULL)
		return (FALSE);
	return (TRUE);
}

t_bool	execution_prepare_heredoc(t_syntax *syntax)
{
	t_list	*lst;

	if (syntax->type == kSubShell)
		return (execution_prepare_heredoc(syntax->subshell->command));
	if (syntax->type == kConnection)
		return (execution_prepare_heredoc(syntax->connect->first)
			&& execution_prepare_heredoc(syntax->connect->second));
	lst = syntax->redirs;
	while (lst != NULL)
	{
		if (!prepare(lst->content))
			return (FALSE);
		lst = lst->next;
	}
	return (TRUE);
}
