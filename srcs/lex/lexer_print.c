/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 23:46:55 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 14:43:12 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static void	init_lex_types(const char *names[])
{
	names[Lex_Greater] = "Lex_Greater";
	names[Lex_DoubleGreater] = "Lex_DoubleGreater";
	names[Lex_Lesser] = "Lex_Lesser";
	names[Lex_DoubleLesser] = "Lex_DoubleLesser";
	names[Lex_InnerDollar] = "Lex_InnerDollar";
	names[Lex_OuterDollar] = "Lex_OuterDollar";
	names[Lex_Ampersand] = "Lex_Ampersand";
	names[Lex_DoubleAmpersand] = "Lex_DoubleAmpersand";
	names[Lex_Bar] = "Lex_Bar";
	names[Lex_DoubleBar] = "Lex_DoubleBar";
	names[Lex_Backslash] = "Lex_Backslash";
	names[Lex_OpenBracket] = "Lex_OpenBracket";
	names[Lex_CloseBracket] = "Lex_CloseBracket";
	names[Lex_String] = "Lex_String";
	names[Lex_Splitter] = "Lex_Splitter";
	names[Lex_Identifier] = "Lex_Identifier";
}

static void	print_lex(t_lex *lex, t_bool has_next)
{
	static const char *names[Lex_Num];

	if (names[0] == NULL)
		init_lex_types(names);
	printf("%s", names[lex->type]);
	if (lex->type == Lex_String || lex->type == Lex_Identifier)
		printf("(%s)", lex->data);
	if (has_next)
		printf(", ");
}

void	print_lexes(t_list *list)
{
	t_elem	*elem;

	printf("lexes=[%d]\n", list->length);
	elem = list->head;
	while (elem != NULL)
	{
		print_lex(elem->data, elem->next != NULL);
		elem = elem->next;
	}
	printf("\n");
}
