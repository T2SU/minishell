/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 18:37:20 by smun              #+#    #+#             */
/*   Updated: 2021/09/01 14:46:41 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

static t_bool	read_secondary_line(int fd, const char *eof)
{
	t_strbuf	strbuf;
	char		*line;

	ft_bzero(&strbuf, sizeof(t_strbuf));
	while (TRUE) // readline 무한루프와 strbuf를 활용해 heredoc 읽기.
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (!ft_strncmp(eof, line, ft_strlen(eof) + 1))
			break ;
		strbuf_appends(&strbuf, line);
		strbuf_append(&strbuf, '\n');
	}
	line = strbuf_get(&strbuf);
	// 다 읽은 다음 해당 heredoc 임시파일에 내용 작성하기
	if (write(fd, line, ft_strlen(line)) < 0)
		exit_error();
	free(line);
	close(fd);
	return (TRUE);
}

static void	signal_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	printf("\n");
	exit(EXIT_FAILURE);
}

static t_bool	read_heredoc(int fd, const char *eof)
{
	pid_t	pid;
	int		status;

	context_get()->heredoc = TRUE;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, &signal_handler);  // SIGINT시 readline 프로세스를 종료시키게 설정.
		signal(SIGQUIT, &signal_handler); // SIGQUIT 시그널은 무시하게 설정
		if (read_secondary_line(fd, eof))
			exit(EXIT_SUCCESS);
		exit(EXIT_FAILURE);
	}
	if (pid < 0)
		exit_error();
	status = 0;
	waitpid(pid, &status, 0);
	context_get()->heredoc = FALSE;
	if (context_is_exited(status) && context_get_exit_status(status) == 0)
		return (TRUE);
	return (FALSE);
}

char	*execution_make_heredoc(t_redir *redir)
{
	const char		*prefix = "/tmp/heredoc_";
	const size_t	prefixlen = ft_strlen(prefix);
	char			*filename;
	t_bool			ret;
	int				fd;

	// 임시 파일이름 생성
	filename = safe_malloc(prefixlen + 32 + 1);
	ft_memcpy(filename, prefix, prefixlen);
	ft_randomstr(&filename[prefixlen], 32);
	filename[prefixlen + 32] = '\0';
	ret = TRUE;
	fd = open(filename, O_APPEND | O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		ret = raise_system_error(filename);
	else if (!read_heredoc(fd, redir->heredoc_eof)) // 실제 heredoc 읽기 루틴
		ret = FALSE;
	close(fd);
	if (!ret)
	{
		unlink(filename);
		free(filename);
		filename = NULL;
	}
	return (filename);
}
