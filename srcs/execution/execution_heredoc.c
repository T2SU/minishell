/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 18:37:20 by smun              #+#    #+#             */
/*   Updated: 2021/08/25 01:50:45 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <fcntl.h>
#include <unistd.h>

/*
rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		*/

static t_bool	read_heredoc(int fd)
{
	// SIGINT가 들어오면 readline을 취소하는 법
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
	filename[prefixlen] = '\0';
	ret = TRUE;
	fd = open(filename, O_APPEND | O_WRONLY | O_CREAT);
	if (fd == -1)
		ret = raise_system_error(filename);
	else if (!read_heredoc(fd))
		ret = FALSE;
	close(fd);
	if (!ret)
		filename = NULL;
	return (filename);
}
