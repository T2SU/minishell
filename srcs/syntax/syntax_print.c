/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:17:22 by smun              #+#    #+#             */
/*   Updated: 2021/08/17 17:26:48 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static void	print_redir(t_redirection *redir)
{
	if (redir->type == RedirType_Write)
		printf(RED" > ");
	if (redir->type == RedirType_ReadDelim)
		printf(RED" << ");
	if (redir->type == RedirType_Append)
		printf(RED" >> ");
	if (redir->type == RedirType_Read)
		printf(RED" < ");
	printf(CYAN"{%s}", redir->name);
}

static void	print_command(t_command *cmd)
{
	char	*word;
	t_list	*cur;
	t_list	*curr;

	cur = cmd->args;
	printf(RED"(");
	while (cur != NULL)
	{
		word = cur->content;
		printf(" ");
		printf(CYAN"{%s}", word);
		cur = cur->next;
	}
	curr = cmd->redirs;
	while (curr != NULL)
	{
		print_redir(curr->content);
		curr = curr->next;
	}
	printf(RED" )");
}

static void	print_job(t_job *job)
{
	printf(GREEN"[ ");
	print_command(job->cmd);
	if (job->pipejob != NULL)
	{
		printf(GREEN" | ");
		print_job(job->pipejob);
	}
	printf(GREEN" ]");
}

void	print_statement(t_statement *statement)
{
	printf(BLUE"《");
	if (statement->type == StatementType_SingleJob)
	{
		print_job(statement->job);
		printf(" ");
	}
	else
	{
		print_statement(statement->first);
		if (statement->type == StatementType_And)
			printf(BLUE"&& ");
		else if (statement->type == StatementType_Or)
			printf(BLUE"|| ");
		if (statement->type != StatementType_Normal)
			print_statement(statement->second);
	}
	printf(BLUE"》"RESET);
}
