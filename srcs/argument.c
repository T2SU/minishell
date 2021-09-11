/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 22:27:38 by smun              #+#    #+#             */
/*   Updated: 2021/09/11 22:35:30 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	insert(char *str, t_list **lst)
{
	t_list	*newlst;

	newlst = ft_lstnew(str);
	if (newlst == NULL)
		exit_error();
	ft_lstadd_back(lst, newlst);
}

static void	add_argument(t_word *word, t_list **lst)
{
	char	*str;

	str = word_get(word, TRUE, FALSE);
	if (str == NULL)
		exit_error();
	if (ft_strlen(str) == 0 && is_consisted_only_variables(word))
	{
		free(str);
		return ;
	}
	insert(str, lst);
}

static void add_variable_argument(t_word *word, t_list **lst)
{
	int		i;
	char	*val;
	char	**splitted;

	val = word_get(word, TRUE, FALSE);
	splitted = ft_split(val, ' ');
	free(val);
	if (splitted == NULL)
		exit_error();
	i = 0;
	while (TRUE)
	{
		val = splitted[i++];
		if (val == NULL)
			break ;
		if (ft_strlen(val) == 0)
			continue ;
		insert(safe_strdup(val), lst);
	}
	free_char_arrays(splitted);
}

char	**parse_arguments(t_simplecmd *scmd, int *argc)
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
		else if (is_consisted_only_variables(wordlst->content))
			add_variable_argument(wordlst->content, &newlst);
		else
			add_argument(wordlst->content, &newlst);
		wordlst = wordlst->next;
	}
	ret = convert_to_array(newlst, kArgument);
	*argc = ft_lstsize(newlst);
	ft_lstclear(&newlst, &free);
	return (ret);
}
