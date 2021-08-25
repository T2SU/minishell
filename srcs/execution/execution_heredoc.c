/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 18:37:20 by smun              #+#    #+#             */
/*   Updated: 2021/08/25 15:30:14 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <fcntl.h>
#include <unistd.h>

static t_bool	read_secondary_line(int fd, const char *eof)
{
	t_strbuf	strbuf;
	char		*line;
	ft_bzero(&strbuf, sizeof(t_strbuf));
	while (TRUE)
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
	if (write(fd, line, ft_strlen(line)) < 0)
		exit_error();
	free(line);
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
		signal(SIGINT, &signal_handler);
		signal(SIGQUIT, &signal_handler);
		if (read_secondary_line(fd, eof))
			exit(EXIT_SUCCESS);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	context_get()->heredoc = FALSE;
	if (status == 0)
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

	filename = safe_malloc(prefixlen + 32 + 1);
	ft_memcpy(filename, prefix, prefixlen);
	ft_randomstr(&filename[prefixlen], 32);
	filename[prefixlen + 32] = '\0';
	ret = TRUE;
	fd = open(filename, O_APPEND | O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		ret = raise_system_error(filename);
	else if (!read_heredoc(fd, redir->heredoc_eof))
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
