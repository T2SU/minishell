/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 01:24:57 by smun              #+#    #+#             */
/*   Updated: 2021/09/01 14:52:26 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

t_bool	execution_set_redir(t_execution *exec, int flags, int fd)
{
	// 기존 in 파일 디스크립터가 있다면 모두 닫기
	if ((flags & kFileIn) && exec->in.fd != 0)
		close(exec->in.fd);
	// 기존 out 파일 디스크립터가 있다면 모두 닫기
	if ((flags & kFileOut) && exec->out.fd != 0)
		close(exec->out.fd);
	if ((flags & kFileIn))
		exec->in.fd = fd;
	if ((flags & kFileOut))
		exec->out.fd = fd;
	return (fd != 0);
}

static void	print_redirection(const char *filename, t_redir *redir)
{
	if (!VERBOSE)
		return ;
	ft_putstr_fd(BLUE" Redir Type : ", STDERR_FILENO);
	if (redir->type == kAppend)
		ft_putstr_fd(RED"Append\n", STDERR_FILENO);
	if (redir->type == kRead)
		ft_putstr_fd(RED"Read\n", STDERR_FILENO);
	if (redir->type == kReadHeredoc)
		ft_putstr_fd(RED"ReadHeredoc\n", STDERR_FILENO);
	if (redir->type == kWrite)
		ft_putstr_fd(RED"Write\n", STDERR_FILENO);
	ft_putstr_fd(BLUE" FileName: "RED, STDERR_FILENO);
	ft_putstr_fd((char *)filename, STDERR_FILENO);
	ft_putstr_fd(RESET"\n", STDERR_FILENO);
}

static t_bool	handle_redirection(t_execution *exec, t_redir *redir)
{
	int		fd;
	char	*filename;
	t_bool	ret;

	if (redir->type == kReadHeredoc)
		filename = safe_strdup(redir->heredoc_file);
	else
		filename = word_get(redir->filename, TRUE, FALSE);
	if (filename == NULL)
		return (FALSE);
	fd = open(filename, redir->flags, 0644);
	if (fd == -1)
		ret = raise_system_error(filename);
	else if (redir->type == kRead || redir->type == kReadHeredoc)
		ret = execution_set_redir(exec, kFileIn, fd);
	else if (redir->type == kWrite || redir->type == kAppend)
		ret = execution_set_redir(exec, kFileOut, fd);
	else
		ret = raise_error(filename, "unknown redirection type");
	print_redirection(filename, redir);
	free(filename);
	return (ret);
}

// 문법 내의 모든 리다이렉션을 처리
t_bool	execution_handle_redirections(t_execution *exec)
{
	t_list		*lst;
	t_syntax	*syntax;

	syntax = exec->syntax;
	lst = syntax->redirs;
	while (lst != NULL)
	{
		if (!handle_redirection(exec, lst->content))
			// 실패하면 모두 해제 후 FALSE 리턴
			return (execution_set_redir(exec, kFileIn | kFileOut, 0));
		lst = lst->next;
	}
	return (TRUE);
}
