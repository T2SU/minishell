/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 15:08:12 by smun              #+#    #+#             */
/*   Updated: 2021/08/09 21:59:50 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

/*
** - String
**   1. char *  - Raw String
**   2. $char * - Environment Variable Name
**
** - Command
**   1. <String>
**   2. <String> <String>
**   3. <String> <String> <String>
**   ...
**
** - Expression
**   1. <Expression> '<' <String>(FileName)
**   2. <Expression> '<<' <String>(EOF Token)
**   3. <Expression> '>' <String>(FileName)
**   4. <Expression> '>>' <String>(FileName)
**   5. <Expression> '|' <Expression>
**   5. <Expression> '&&' <Expression>
**   5. <Expression> '||' <Expression>
**
** - SubShell '(', ')'
**   1. <Expression>
*/

t_syntax	*syntax_parse(t_parser *parser)
{
	t_lex		*lex;
	t_syntax	*syntax;

	while (parser->current != NULL)
	{
		lex = parser->current->data;

		parser->current = parser->current->next;
	}
}
