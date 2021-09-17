/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 22:27:38 by smun              #+#    #+#             */
/*   Updated: 2021/09/17 19:25:59 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		else if (is_single_dollar_sign(wordlst->content))
			insert_to_list("$", &newlst);
		else
			word_get_as_list(wordlst->content, &newlst);
		wordlst = wordlst->next;
	}
	ret = convert_to_array(newlst, kArgument);
	*argc = ft_lstsize(newlst);
	ft_lstclear(&newlst, &free);
	return (ret);
}
