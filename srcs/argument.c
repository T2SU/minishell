/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 22:27:38 by smun              #+#    #+#             */
/*   Updated: 2021/09/12 22:13:27 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	flush_to_argument(char *arr[], int max, t_list **lst, t_bool final)
{
	t_list	*newlst;
	int		i;

	i = -1;
	while (++i < max)
	{
		if (arr[i] == NULL)
			break ;
		if (!final && ft_strlen(arr[i]) == 0)
			continue ;
		newlst = ft_lstnew(safe_strdup(arr[i]));
		if (newlst == NULL)
			exit_error();
		ft_lstadd_back(lst, newlst);
	}
}

static void	iterate_chunks(t_strbuf *strbuf, t_wordchunk *chunk, t_list **lst)
{
	char	*str;
	char	**splitted;
	int		size;

	if (chunk->flag == WordFlag_None)
		str = chunk->str;
	else
		str = expand_variable(chunk);
	strbuf_appends(strbuf, str);
	if (chunk->quote || !ft_strchr(str, ' '))
		return ;
	str = strbuf_get(strbuf);
	splitted = ft_split(str, ' ');
	if (splitted == NULL)
		exit_error();
	size = get_vector_size(splitted);
	flush_to_argument(splitted, size - 1, lst, FALSE);
	strbuf_appends(strbuf, splitted[size - 1]);
	free_char_arrays(splitted);
}

static void	process_word(t_word *word, t_list **lst)
{
	t_strbuf	strbuf;
	t_list		*chunklst;
	char		*laststr;

	ft_bzero(&strbuf, sizeof(t_strbuf));
	chunklst = word->wordlist;
	while (chunklst)
	{
		iterate_chunks(&strbuf, chunklst->content, lst);
		chunklst = chunklst->next;
	}
	laststr = strbuf_get(&strbuf);
	flush_to_argument((char *[]){laststr, NULL}, 1, lst, TRUE);
	free(laststr);
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
		else
			process_word(wordlst->content, &newlst);
		wordlst = wordlst->next;
	}
	ret = convert_to_array(newlst, kArgument);
	*argc = ft_lstsize(newlst);
	ft_lstclear(&newlst, &free);
	return (ret);
}
