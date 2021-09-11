/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 19:05:46 by smun              #+#    #+#             */
/*   Updated: 2021/09/11 22:18:31 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_consisted_only_variables(t_word *word)
{
	t_list		*lst;
	t_wordchunk	*chunk;

	lst = word->wordlist;
	while (lst != NULL)
	{
		chunk = lst->content;
		if (chunk->flag != WordFlag_DollarSign)
			return (FALSE);
		lst = lst->next;
	}
	return (TRUE);
}
