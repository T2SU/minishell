/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 13:46:05 by smun              #+#    #+#             */
/*   Updated: 2021/08/17 14:09:51 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	free_command(t_command *cmd)
{
	if (cmd == NULL)
		return ;
	ft_lstclear(&cmd->args, &free);
	ft_lstclear(&cmd->redirs, &free);
}

void	free_job(t_job *job)
{
	if (job == NULL)
		return ;
	free_command(job->cmd);
	free_job(job->pipejob);
	free(job);
}

void	free_statement(t_statement *statement)
{
	if (statement == NULL)
		return ;
	free_job(statement->job);
	free_statement(statement->first);
	free_statement(statement->second);
	free(statement);
}
