/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_simplecmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 16:21:06 by smun              #+#    #+#             */
/*   Updated: 2021/09/11 19:49:41 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>

static void	add_argument(t_word *word, t_list **lst)
{
	char	*str;
	t_list	*newlst;

	str = word_get(word, TRUE, FALSE);
	if (str == NULL)
		exit_error();
	if (ft_strlen(str) == 0 && is_consisted_only_variables(word))
	{
		free(str);
		return ;
	}
	newlst = ft_lstnew(str);
	if (newlst == NULL)
		exit_error();
	ft_lstadd_back(lst, newlst);
}

static char	**parse_arguments(t_simplecmd *scmd, int *argc)
{
	t_list	*wordlst;
	t_list	*newlst;
	char	**ret;

	wordlst = scmd->args;
	newlst = NULL;
	while (wordlst != NULL)
	{
		if (is_wildcard(wordlst->content))
			expand_wildcard(&newlst);
		else
			add_argument(wordlst->content, &newlst);
		wordlst = wordlst->next;
	}
	ret = convert_to_array(newlst, kArgument);
	*argc = ft_lstsize(newlst);
	ft_lstclear(&newlst, &free);
	return (ret);
}

void	free_char_arrays(char *arrays[])
{
	int		i;

	i = 0;
	if (arrays)
	{
		while (arrays[i])
			free(arrays[i++]);
		if (arrays)
			free(arrays);
	}
}

static int	command_run_external(char *path, char *argv[], char *envp[])
{
	int		status;
	pid_t	pid;

	//fork 후 execve
	pid = fork();
	if (pid == 0)
	{
		// 파일이 없거나 하면 에러..
		if (!is_exist(path))
		{
			raise_system_error(path);
			exit(127);
		}
		// 디렉토리를 열려고 하면 EISDIR 에러를 줘야함.
		else if (is_dir(path))
			raise_error(path, "is a directory");
		// 자식 프로세스
		else if (execve(path, argv, envp) == -1)
			raise_system_error(path);
		exit(126);
	}
	if (pid < 0)
		exit_error();
	// 부모는 자식프로세스 종료까지 대기 및 반환코드 얻기
	waitpid(pid, &status, 0);
	if (context_is_signaled(status) && context_has_flag(kInSubShell))
		context_get()->flag |= kThrowed;
	if (!context_has_flag(kInChildProc))
		context_print_strsignal(status);
	return (status);
}

int	execution_simplecmd_run(t_simplecmd *scmd)
{
	t_input	input;
	t_dict	*dict;
	int		status;
	char	*new_cmd;
	char	*cmd;

	dict = context_get()->env;
	input.argv = parse_arguments(scmd, &input.argc);
	// 빌트인 or 외부 커맨드
	new_cmd = is_path_command(input.argv[0], dict);
	if (input.argc == 0)
		status = EXIT_SUCCESS;
	else if (!is_command(input.argv[0]) || new_cmd)
	{
		input.envp = convert_to_array(dict->head, kEnvironment);
		cmd = new_cmd;
		if (!is_command(input.argv[0]))
			cmd = input.argv[0];
		status = command_run_external(cmd, input.argv, input.envp);
		free_char_arrays(input.envp);
	}
	else
		status = command_run_builtin(input.argc, input.argv, dict); // 실행 후 리턴 코드 얻기
	// 정리 후 반환코드 리턴
	free(new_cmd);
	free_char_arrays(input.argv);
	return (status);
}
