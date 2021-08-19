/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 00:24:41 by smun              #+#    #+#             */
/*   Updated: 2021/08/19 16:18:10 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

char	*expand_variable(char *name)
{
	char	*ret;

	ret = ft_strdup(name);
	if (ret == NULL)
		exit_error();
	return (ret);
}

char	*word_get(t_word *word, t_bool expand_vars)
{
	t_strbuf	strbuf;
	t_list		*lst;
	t_wordchunk	*chunk;

	ft_memset(&strbuf, 0, sizeof(t_strbuf));
	lst = word->wordlist;
	while (lst != NULL)
	{
		chunk = lst->content;
		if (!expand_vars && chunk->flag != WordFlag_None)
			strbuf_append(&strbuf, '$');
		if (!expand_vars || chunk->flag == WordFlag_None)
			strbuf_appends(&strbuf, chunk->str);
		else
			strbuf_appends(&strbuf, expand_variable(chunk->str));
		lst = lst->next;
	}
	ft_lstclear(&word->wordlist, &dispose_wordchunk);
	free(word);
	return (strbuf_get(&strbuf));
}
