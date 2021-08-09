/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr_build_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:22:53 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 23:44:43 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_string_syntax(void *ptr)
{
	t_syntax	*syntax;

	syntax = (t_syntax *)ptr;
	if (syntax == NULL || syntax->type != Syntax_String)
		return ;
	free(syntax->data.string.name);
	free(syntax);
}

void	collect_token(t_list *collected, t_strbuf *strbuf)
{
	t_syntax	*syntax;
	char		*str;

	if (strbuf_length(strbuf) == 0)
		return ;
	str = strbuf_get(strbuf, TRUE);
	if (str == NULL)
		exit_error(get_context()->executable_name);
	syntax = malloc(sizeof(t_syntax));
	if (syntax == NULL)
		exit_error(get_context()->executable_name);
	syntax->data.string.name = str;
	syntax->data.string.variable = FALSE;
	syntax->type = Syntax_String;
	if (!list_add(collected, syntax, &free_string_syntax))
		exit_error(get_context()->executable_name);
}

t_bool	parse_variable(t_list *collected, t_list *list, t_elem *cur)
{
	t_lex		*lex;
	t_syntax	*syntax;
	char		*str;

	cur = cur->next;
	if (cur == NULL)
		return (FALSE);
	lex = cur->data;
	if (lex->type != Lex_Identifier)
		return (FALSE);
	str = ft_strdup(lex->data);
	syntax = malloc(sizeof(t_syntax));
	if (str == NULL || syntax == NULL)
	{
		free(str);
		free(syntax);
		return (FALSE);
	}
	syntax->type = Syntax_String;
	syntax->data.string.name = str;
	syntax->data.string.variable = TRUE;
	list_remove_if(list, cur);
	if (!list_add(collected, syntax, &free_string_syntax))
		exit_error(get_context()->executable_name);
	return (TRUE);
}
