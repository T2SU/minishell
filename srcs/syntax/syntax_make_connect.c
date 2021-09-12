/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_make_connect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:58:24 by smun              #+#    #+#             */
/*   Updated: 2021/09/12 17:28:24 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_syntax	*bond(t_syntax *first, t_syntax *second, int type)
{
	t_connect	*con;

	con = safe_malloc(sizeof(t_connect));
	con->second = second;
	con->first = first;
	con->connector = type;
	return (syntax_make(con, kConnection));
}

void	syntax_make_connection(t_stack *st, int type)
{
	t_syntax	*second;
	t_syntax	*first;

	second = stack_pop(st);
	free(stack_pop(st));
	first = stack_pop(st);
	stack_push(st, bond(first, second, type));
}

static t_syntax	*find_simplecmd_at_the_end(t_syntax *con)
{
	t_syntax	*syn;

	syn = con;
	while (TRUE)
	{
		syn = syn->connect->second;
		if (syn->type == kSimpleCommand)
			return (syn);
		else if (syn->type == kConnection)
			continue ;
		else
			return (NULL);
	}
}

void	syntax_append_argument_to_connect(t_stack *st)
{
	t_list		*wordlst;
	t_word		*word;
	t_syntax	*consyntax;
	t_syntax	*cmdsyntax;

	word = syntax_strip(stack_pop(st), kWord);
	consyntax = stack_pop(st);
	cmdsyntax = find_simplecmd_at_the_end(consyntax);
	wordlst = ft_lstnew(word);
	if (wordlst == NULL)
		exit_error();
	ft_lstadd_back(&cmdsyntax->simplecmd->args, wordlst);
	stack_push(st, consyntax);
}

/*
** connect | cmd
** —>
** newcon(con->first, con->second | cmd)
*/

void	syntax_separate_bond_connect(t_stack *st)
{
	t_connect	*oldcon;
	t_syntax	*cmdsyntax;
	t_syntax	*secondsyn;
	t_syntax	*newconsyn;

	cmdsyntax = stack_pop(st);
	free(stack_pop(st));
	oldcon = syntax_strip(stack_pop(st), kConnection);
	secondsyn = bond(oldcon->second, cmdsyntax, kPipe);
	newconsyn = bond(oldcon->first, secondsyn, oldcon->connector);
	free(oldcon);
	stack_push(st, newconsyn);
}
