/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 13:46:05 by smun              #+#    #+#             */
/*   Updated: 2021/08/17 19:06:37 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void	free_redirection(void *ptr)
{
	t_redirection	*redir;

	redir = (t_redirection *)ptr;
	free(redir->name);
	free(redir);
}

void	*free_command(t_command *cmd)
{
	if (cmd == NULL)
		return (NULL);
	ft_lstclear(&cmd->args, &free);
	ft_lstclear(&cmd->redirs, &free_redirection);
	free(cmd);
	return (NULL);
}

void	*free_job(t_job *job)
{
	if (job == NULL)
		return (NULL);
	free_command(job->cmd);
	free_job(job->pipejob);
	free(job);
	return (NULL);
}

void	*free_statement(t_statement *statement)
{
	if (statement == NULL)
		return (NULL);
	free_job(statement->job);
	free_statement(statement->first);
	free_statement(statement->second);
	free(statement);
	return (NULL);
}
