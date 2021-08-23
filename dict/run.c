/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 18:42:04 by hkim              #+#    #+#             */
/*   Updated: 2021/08/23 21:18:23 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

void	run_cd(t_list *args, char *home)
{
	if (ft_lstsize(args) > 1)
		printf("cd: too many arguments\n");
	else if (ft_lstsize(args) == 1)
	{
		if (chdir((char *)args->content) == -1)
			printf("cd: %s: %s\n", (char *)args->content, strerror(errno));
	}
	else if (ft_lstsize(args) == 0)
	{
		if (chdir(home) == -1)
			printf("cd: %s\n", strerror(errno));
	}
}

void	run_pwd(void)
{
	char	path[PATH_MAX];

	getcwd(path, PATH_MAX);
	printf("%s\n", path);
}

int	is_str_num(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			res = 0;
			break ;
		}
		i++;
	}
	return (res);
}

void	run_exit(t_list *args)
{
	printf("exit\n");
	if (ft_lstsize(args) == 0)
		exit(0);
	else if (!is_str_num(args->content))
	{
		printf("exit: %s: numeric argument required\n", (char *)args->content);
		exit(1);
	}
	else if (ft_lstsize(args) > 1)
		printf("exit: too many arguments\n");
	else
		exit(ft_atoi(args->content));
}

/*
int	main(int argc, char **argv, char **envp)
{
	t_list	*list;
	t_list	*list2;
	t_dict	*dict;
	char	*home;

	argc = argc;
	argv = argv;
	dict = make_dict(envp);
	home = dict_get(dict, "HOME");
	run_pwd();
	// 인자가 하나일때
	list = NULL;
	ft_lstadd_back(&list, ft_lstnew("../"));
	run_cd(list, home);
	run_pwd();
	// 인자가 없을때
	run_cd(NULL, home);
	run_pwd();
	// 인자가 두개일때
	ft_lstadd_back(&list, ft_lstnew("test"));
	run_cd(list, home);
	run_pwd();
	free(list->next);
	free(list);
	// 인자가 없는 path
	list2 = NULL;
	ft_lstadd_back(&list2, ft_lstnew("abc"));
	run_cd(list2, home);
	run_pwd();
	free(list2);
	dict_free(dict);
}
*/
// int main()
// {
// 	t_list	*list;
// 	t_list	*list2;

// 	// 인자가 없을때
// 	while(1)
// 		run_exit(NULL);

	// 인자가 하나일때
	// list = NULL;
	// ft_lstadd_back(&list, ft_lstnew("2"));
	// while (1)
	// 	run_exit(list);

// 	// 인자가 숫자가 아닐때
// 	list2 = NULL;
// 	ft_lstadd_back(&list2, ft_lstnew("7a"));
// 	while (1)
// 		run_exit(list2);

// 	// 인자가 많을때
// 	list = NULL;
// 	ft_lstadd_back(&list, ft_lstnew("1"));
// 	ft_lstadd_back(&list, ft_lstnew("5"));
// 	while (1)
// 		run_exit(list);
// }
