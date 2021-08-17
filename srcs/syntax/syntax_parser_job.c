/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parser_job.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 23:48:24 by smun              #+#    #+#             */
/*   Updated: 2021/08/17 13:50:40 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_job	*with_pipe(t_parser *parser, t_job *job)
{
	parser->cur = parser->cur->next;
	job->pipejob = next_job(parser);
	if (job->pipejob == NULL)
	{
		free_command(job->cmd);
		free(job);
		return (NULL);
	}
	return (job);
}

t_job	*next_job(t_parser *parser)
{
	t_job		*ret;
	t_command	*cmd;

	cmd = next_command(parser);
	if (cmd == NULL)
	{
		free_command(cmd);
		return (NULL);
	}
	skip_whitespaces(parser);
	ret = malloc(sizeof(t_job));
	if (ret == NULL)
		exit_error();
	ret->cmd = cmd;
	ret->pipejob = NULL;
	if (is_acceptable(parser->cur, Token_Bar))
		return (with_pipe(parser, ret));
	return (ret);
}
