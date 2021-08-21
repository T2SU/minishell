/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testlib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 16:15:05 by smun              #+#    #+#             */
/*   Updated: 2021/08/21 23:10:23 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testlib.h"
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define RESET "\033[0m"

static void		apply_result(int print, int status, const char *module_name)
{
	static int	total;
	static int	failed;

	if (print)
	{
		printf(RESET"   "YELLOW"%-24s"RESET"RESULT\n", module_name);
		printf("%-26s[%6d]\n", " - "CYAN"TOTAL:                 ", total);
		printf("%-26s[%6d]\n", " - "GREEN"SUCCESS:               ", total - failed);
		printf("%-26s[%6d]\n", " - "RED"FAILED:                ", failed);
		printf(WHITE"-------------------------------------"RESET"\n");
	}
	else
	{
		total++;
		if (status != EXIT_SUCCESS)
			failed++;
	}
}

void			print_test_result(int argc, const char *module_name)
{
	(void)argc;
	apply_result(1, 0, module_name);
}

/*
** Do some test with a new child process.
** Returns its last status code.
*/

int				do_test(void(*testfunc)())
{
	int			status;
	pid_t		pid;

	pid = fork();
	if (!pid)
	{
		write(STDOUT_FILENO, RED, 5);
		testfunc();
		write(STDOUT_FILENO, RESET, 4);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
	apply_result(0, status, NULL);
	return (status);
}

static void		print_stdout_information(const char *compare, char *your, size_t len)
{
	char	*copy_compare;
	char	*copy_your;

	copy_compare = strdup(compare);
	copy_your = strndup(your, len);
	printf(GREEN"====expected output====\n");
	printf("%s\n", copy_compare);
	printf("\n");
	printf(RED"====your output====\n");
	printf("%s\n", copy_your);
	printf("\n");
	free(copy_compare);
	free(copy_your);
}

static int		compare_with_fd(const char *compare, int fd)
{
	char		buffer[4096];
	size_t		compare_index;
	ssize_t		size;

	compare_index = 0;
	size = 0;
	while(1)
	{
		size = read(fd, buffer, sizeof(buffer));
		if (size < 0)
			return (-1);
		if (size == 0)
			break ;
		if (memcmp(&compare[compare_index], buffer, size))
		{
			print_stdout_information(&compare[compare_index], buffer, size);
			return (1);
		}
		compare_index += size;
	}
	if (strlen(compare) != compare_index)
	{
		print_stdout_information(&compare[compare_index], buffer, size);
		printf(RED"different stdout size. expected:%zu (your:%zu)\n", strlen(compare), compare_index);
		return (1);
	}
	return (0);
}

static int		count_newline(int fd)
{
	char		buffer[1024];
	int			count;

	count = 0;
	while(1)
	{
		ssize_t size = read(fd, buffer, sizeof(buffer));
		if (size < 0)
			return (-1);
		if (size == 0)
			break ;
		for (int i = 0; i < size; i++)
			if (buffer[i] == '\n')
				count++;
	}
	return (count);
}

static int		pipe_child(void(*testfunc)(), int *fd, pid_t *ppid)
{
	if (pipe(fd) == -1)
	{
		apply_result(0, SIGABRT, NULL);
		return (SIGABRT);
	}
	*ppid = fork();
	if (!(*ppid))
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		testfunc();
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	close(fd[1]);
	return (0);
}

int				do_test_stdout_real(void(*testfunc)(), const char *file, int line, const char *compare)
{
	int			fd[2];
	int			status;
	pid_t		pid;

	if (0 == (status = pipe_child(testfunc, fd, &pid)))
	{
		waitpid(pid, &status, 0);
		if (compare_with_fd(compare, fd[0]))
		{
			printf(RED"failed: different stdout - %s:%d"RESET"\n", file, line);
			status = SIGABRT;
		}
		close(fd[0]);
		apply_result(0, status, NULL);
	}
	return (status);
}

int				do_test_count_newline_real(void(*testfunc)(), const char *file, int line, int max_newline_count)
{
	int			fd[2];
	int			status;
	pid_t		pid;

	if (0 == (status = pipe_child(testfunc, fd, &pid)))
	{
	waitpid(pid, &status, 0);
	int count = count_newline(fd[0]);
	if (count > max_newline_count)
	{
		printf(RED"failed: too many instructions (your:%d) (max:%d) - %s:%d"RESET"\n",
			count, max_newline_count, file, line);
		status = SIGABRT;
	}
	close(fd[0]);
	apply_result(0, status, NULL);
	}
	return (status);
}
