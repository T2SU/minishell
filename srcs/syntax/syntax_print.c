/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:17:22 by smun              #+#    #+#             */
/*   Updated: 2021/08/17 15:56:47 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static void print_job(t_job *job)
{
	t_list			*cur;
	t_list			*curr;
	char			*word;
	t_redirection	*redir;

	cur = job->cmd->args;
	printf("[ ");
	printf("(");
	while (cur != NULL)
	{
		word = cur->content;
		printf(" ");
		printf("{%s}", word);
		cur = cur->next;
	}
	curr = job->cmd->redirs;
	while (curr != NULL)
	{
		redir = curr->content;
		if (redir->type == RedirType_Write)
			printf(" > ");
		if (redir->type == RedirType_ReadDelim)
			printf(" << ");
		if (redir->type == RedirType_Append)
			printf(" >> ");
		if (redir->type == RedirType_Read)
			printf(" < ");
		printf("{%s}", redir->name);
		curr = curr->next;
	}
	printf(" )");
	if (job->pipejob != NULL)
	{
		printf(" | ");
		print_job(job->pipejob);
	}
	printf(" ]");
}

void	print_statement(t_statement *statement)
{
	printf("《");
	if (statement->type == StatementType_SingleJob)
	{
		print_job(statement->job);
		printf(" ");
	}
	else
	{
		print_statement(statement->first);
		if (statement->type == StatementType_And)
			printf(" && ");
		else if (statement->type == StatementType_Or)
			printf(" || ");
		if (statement->type != StatementType_Normal)
			print_statement(statement->second);
	}
	printf("》");
}
