/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 23:46:55 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 01:02:40 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static void	init_lex_types(const char *names[])
{
	names[kGreater] = "kGreater";
	names[kDoubleGreater] = "kDoubleGreater";
	names[kLesser] = "kLesser";
	names[kDoubleLesser] = "kDoubleLesser";
	names[kInnerDollar] = "kInnerDollar";
	names[kOuterDollar] = "kOuterDollar";
	names[kAmpersand] = "kAmpersand";
	names[kDoubleAmpersand] = "kDoubleAmpersand";
	names[kBar] = "kBar";
	names[kDoubleBar] = "kDoubleBar";
	names[kBackslash] = "kBackslash";
	names[kOpenBracket] = "kOpenBracket";
	names[kCloseBracket] = "kCloseBracket";
	names[kString] = "kString";
	names[kSplitter] = "kSplitter";
	names[kIdentifier] = "kIdentifier";
}

static void	print_lex(t_lex *lex, t_bool has_next)
{
	static const char *names[kLexNum];

	if (names[0] == NULL)
		init_lex_types(names);
	printf("%s", names[lex->type]);
	if (lex->type == kString || lex->type == kIdentifier)
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
