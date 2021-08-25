/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_simplecmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 16:21:06 by smun              #+#    #+#             */
/*   Updated: 2021/08/25 19:41:32 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 임시 함수
t_bool	command_is_builtin(const char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 5))
		return (TRUE);
	return (FALSE);
}

// 임시 함수
static int	command_run_builtin(int argc, char *argv[], char *envp[])
{
	int	i;

	(void)envp;
	if (argc <= 0)
		return (EXIT_FAILURE);
	if (!ft_strncmp(argv[0], "echo", 5))
	{
		i = 1;
		while (i < argc)
		{
			if (i != 1)
				write(STDOUT_FILENO, " ", 1);
			write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
			i++;
		}
		write(STDOUT_FILENO, "\n", 1);
		return (EXIT_SUCCESS);
	}
	raise_error(argv[0], "command not found");
	return (EXIT_FAILURE);
}

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

int	execution_simplecmd_run(t_simplecmd *scmd)
{
	int		argc;
	char	**argv;
	char	**envp;
	int		status;
	pid_t	pid;

	// argv, envp 파싱
	argc = ft_lstsize(scmd->args);
	envp = safe_malloc(sizeof(char *) * 1);
	argv = safe_malloc(sizeof(char *) * (1 + argc));
	envp[0] = NULL;
	parse_arguments(argc, argv, scmd);
	// 빌트인 or 외부 커맨드
	if (command_is_builtin(argv[0]))
	{
		// 실행 후 리턴 코드 얻기
		status = command_run_builtin(argc, argv, envp);
	}
	else
	{
		//fork 후 execve
		pid = fork();
		if (pid == 0)
		{
			// 자식 프로세스
			if (execve(argv[0], argv, envp) == -1)
				raise_system_error(argv[0]);
			exit(EXIT_FAILURE);
		}
		if (pid < 0)
			exit_error();
		// 부모는 자식프로세스 종료까지 대기
		waitpid(pid, &status, 0);
	}
	// 강제 종료면(=is_continuable이 거짓) FALSE 리턴.
	// 성공이던 실패던 정상 종료면 TRUE 리턴.
	clean_arguments(argv, envp);
	return (status);
}
