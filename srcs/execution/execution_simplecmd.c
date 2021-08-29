/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_simplecmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 16:21:06 by smun              #+#    #+#             */
/*   Updated: 2021/08/29 14:20:48 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>

static void	parse_arguments(int argc, char *argv[], t_simplecmd *scmd)
{
	t_list	*lst;
	int		i;

	i = 0;
	lst = scmd->args;
	while (i < argc)
	{
		argv[i++] = word_get(lst->content, TRUE, FALSE);
		lst = lst->next;
	}
	argv[argc] = NULL;
}

static void	clean_arguments(char *argv[], char *envp[])
{
	int		i;

	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

static int command_run_external(char *argv[], char *envp[])
{
	int		status;
	pid_t	pid;

	//fork 후 execve
	pid = fork();
	if (pid == 0)
	{
		// 디렉토리를 열려고 하면 EISDIR 에러를 줘야함.
		if (is_dir(argv[0]))
			raise_error(argv[0], "is a directory");
		// 자식 프로세스
		else if (execve(argv[0], argv, envp) == -1)
			raise_system_error(argv[0]);
		exit(EXIT_FAILURE);
	}
	if (pid < 0)
		exit_error();
	// 부모는 자식프로세스 종료까지 대기 및 반환코드 얻기
	waitpid(pid, &status, 0);
	if (context_is_signaled(status)) // 시그널로 종료되면 개행 한번..
		printf("\n");
	return (status);
}

int	execution_simplecmd_run(t_simplecmd *scmd)
{
	int		argc;
	char	**argv;
	char	**envp;
	t_dict	*dict;
	int		status;

	// argv, envp 파싱
	argc = ft_lstsize(scmd->args);
	envp = safe_malloc(sizeof(char *) * 1);
	argv = safe_malloc(sizeof(char *) * (1 + argc));
	envp[0] = NULL;
	dict = context_get()->env;
	parse_arguments(argc, argv, scmd);
	// 빌트인 or 외부 커맨드
	if (command_is_builtin(argv[0]))
		status = command_run_builtin(argc, argv, dict); // 실행 후 리턴 코드 얻기
	else
		status = command_run_external(argv, envp);
	// 정리 후 반환코드 리턴
	clean_arguments(argv, envp);
	return (status);
}
