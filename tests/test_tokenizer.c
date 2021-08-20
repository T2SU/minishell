/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 18:03:24 by smun              #+#    #+#             */
/*   Updated: 2021/08/20 17:49:07 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testlib.h"
#include "minishell.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

static t_bool	assert_token(const char *str, int count, ...);

enum e_tokenize_status
{
	kTokenizeOk,
	kTokenizeFailed,
	kAssertFailed
};

static void	test_empty(void)
{
	t_tokenizer	tokenizer;

	tokenizer.quote = 0;
	tokenizer.str = "";
	assert(tokenize(&tokenizer) == NULL);
	tokenizer.quote = 0;
	tokenizer.str = " ";
	assert(tokenize(&tokenizer) == NULL);
	tokenizer.quote = 0;
	tokenizer.str = "               ";
	assert(tokenize(&tokenizer) == NULL);
	tokenizer.quote = 0;
	tokenizer.str = "       \t      ";
	assert(tokenize(&tokenizer) == NULL);
	tokenizer.quote = 0;
	tokenizer.str = "   \t\t \r   \t  \n\n\t    ";
	assert(tokenize(&tokenizer) == NULL);
}

static void	test_word_simple1(void)
{
	assert(assert_token("echo",
		1,
			kWord,
				0, "echo",
				"echo"
		)
	);
	assert(assert_token("h1e2l3",
		1,
			kWord,
				0, "h1e2l3",
				"h1e2l3"
		)
	);
	assert(assert_token("h-e_l!",
		1,
			kWord,
				0, "h-e_l!",
				"h-e_l!"
		)
	);
	assert(assert_token("123",
		1,
			kWord,
				0, "123",
				"123"
		)
	);
}

static void	test_word_special_dispatches(void)
{
	assert(assert_token("!@#&?",
		1,
			kWord,
				0, "!@#&?",
				"!@#&?"
		)
	);
	assert(assert_token("&",
		1,
			kWord,
				0, "&",
				"&"
		)
	);
	assert(assert_token("?&?",
		1,
			kWord,
				0, "?&?",
				"?&?"
		)
	);
}

static void	test_word_simple_var1(void)
{
	assert(assert_token("$?",
		1,
			kWord,
				WordFlag_LastExitCode, "?",
				"$?"
		)
	);
	assert(assert_token("$HHH-_",
		1,
			kWord,
				WordFlag_DollarSign, "HHH",
				0, "-_",
				"$HHH-_"
		)
	);
	assert(assert_token("$HHH",
		1,
			kWord,
				WordFlag_DollarSign, "HHH",
				"$HHH"
		)
	);
	assert(assert_token("$$123Go",
		1,
			kWord,
				WordFlag_DollarSign, "",
				WordFlag_DollarSign, "123Go",
				"$$123Go"
		)
	);
	assert(assert_token("$",
		1,
			kWord,
				WordFlag_DollarSign, "",
				"$"
		)
	);
}

static void	test_token_special(void)
{
	assert(assert_token("&&&&&&&",
		4,
			kAndAnd, "&&",
			kAndAnd, "&&",
			kAndAnd, "&&",
			kWord,
				WordFlag_None, "&",
				"&"
		)
	);
}

static void	test_token_simple(void)
{
	assert(assert_token("><|<<>>",
		5,
			'>', ">",
			'<', "<",
			'|', "|",
			kLessLess, "<<",
			kGreaterGreater, ">>"
		)
	);
	assert(assert_token("()",
		5,
			'(', "(",
			')', ")"
		)
	);
}

static void	test_token_complex(void)
{
	assert(assert_token("(<(&&)&)",
		6,
			'(', "(",
			'<', "<",
			kAndAnd, "&&",
			')', ")",
			kWord,
				WordFlag_None, "&",
				"&",
			')', ")"
		)
	);
	assert(assert_token("<<&>>&&<|&||",
		8,
			kLessLess, "<<",
			kWord,
				WordFlag_None, "&",
				"&",
			kGreaterGreater, ">>",
			kAndAnd, "&&",
			'<', "<",
			'|', "|",
			kWord,
				WordFlag_None, "&",
				"&",
			kBarBar, "||"
		)
	);
}

static void	test_word_quotes(void)
{
	assert(assert_token("'he llo'",
		1,
			kWord,
				WordFlag_None, "he llo",
				"he llo"
		)
	);
	assert(assert_token("' hello '",
		1,
			kWord,
				WordFlag_None, " hello ",
				" hello "
		)
	);
	assert(assert_token("''",
		1,
			kWord,
				WordFlag_None, "",
				""
		)
	);
}

static void	test_word_quotes_with_consecutive(void)
{
	assert(assert_token("'he llo'dasd'd g'",
		1,
			kWord,
				WordFlag_None, "he llo",
				WordFlag_None, "dasd",
				WordFlag_None, "d g",
				"he llodasdd g"
		)
	);
	assert(assert_token("' hello ''ddd''  '",
		1,
			kWord,
				WordFlag_None, " hello ",
				WordFlag_None, "ddd",
				WordFlag_None, "  ",
				" hello ddd  "
		)
	);
	assert(assert_token("''''",
		1,
			kWord,
				WordFlag_None, "",
				""
		)
	);
}

static void	test_word_quotes_with_consecutive_and_var(void)
{
	assert(assert_token("B$A'C'",
		1,
			kWord,
				WordFlag_None, "B",
				WordFlag_DollarSign, "A",
				WordFlag_None, "C",
				"B$AC"
		)
	);
	assert(assert_token("AB'C$DE 'FG'H'I",
		1,
			kWord,
				WordFlag_None, "AB",
				WordFlag_None, "C$DE ",
				WordFlag_None, "FG",
				WordFlag_None, "H",
				WordFlag_None, "I",
				"ABC$DE FGHI"
		)
	);
}

static void	test_word_quotes_no_escaping(void)
{
	assert(assert_token("'hello \\''go'               g",
		2,
			kWord,
				WordFlag_None, "hello \\",
				WordFlag_None, "go",
				"hello \\go",
			kWord,
				WordFlag_None, "g",
				"g"
		)
	);
	assert(assert_token("'\\n''\\r''\\\\''\\\"'",
		1,
			kWord,
				WordFlag_None, "\\n",
				WordFlag_None, "\\r",
				WordFlag_None, "\\\\",
				WordFlag_None, "\\\"",
				"\\n\\r\\\\\\\""
		)
	);
	assert(assert_token("'$\\'",
		1,
			kWord,
				WordFlag_None, "$\\",
				"$\\"
		)
	);
}

static void	test_word_dquotes(void)
{
	assert(assert_token("\" hello \"",
		1,
			kWord,
				WordFlag_None, " hello ",
				" hello "
		)
	);
	assert(assert_token("\" hello \"hello\" world \"",
		1,
			kWord,
				WordFlag_None, " hello ",
				WordFlag_None, "hello",
				WordFlag_None, " world ",
				" hello hello world "
		)
	);
	assert(assert_token("\" $HELLO \"",
		1,
			kWord,
				WordFlag_None, " ",
				WordFlag_DollarSign, "HELLO",
				WordFlag_None, " ",
				" $HELLO "
		)
	);
}

static void	test_word_dquotes_with_escaping(void)
{
	assert(assert_token("\" $HELLO \\\"zero\\\"\"  \" hello \\\"zer \"",
		1,
			kWord,
				WordFlag_None, " ",
				WordFlag_DollarSign, "HELLO",
				WordFlag_None, "\"zero\"",
				" $HELLO \"zero\"",
			kWord,
				WordFlag_None, " hello \"zer ",
				" hello \"zer "
		)
	);
}

static void	test_word_and_token(void)
{
	assert(assert_token("echo $USER world |cat >file.txt",
		7,
			kWord,
				WordFlag_None, "echo",
				"echo",
			kWord,
				WordFlag_DollarSign, "USER",
				"$USER",
			kWord,
				WordFlag_None, "world",
				"world",
			'|', "|",
			kWord,
				WordFlag_None, "cat",
				"cat",
			'>', ">",
			kWord,
				WordFlag_None, "file.txt",
				"file.txt"
		)
	);
	assert(assert_token("$US\"E$R\"    wo$?rld\"$?\"",
		2,
			kWord,
				WordFlag_DollarSign, "US",
				WordFlag_None, "E",
				WordFlag_DollarSign, "R",
				"$USE$R",
			kWord,
				WordFlag_None, "wo",
				WordFlag_LastExitCode, "?",
				WordFlag_None, "rld",
				WordFlag_LastExitCode, "?",
				"wo$?rld$?"
		)
	);
}

int		main(int argc, char *argv[])
{
	do_test(&test_empty);
	do_test(&test_word_simple1);
	do_test(&test_word_special_dispatches);
	do_test(&test_word_simple_var1);
	do_test(&test_token_simple);
	do_test(&test_token_special);
	do_test(&test_token_complex);
	do_test(&test_word_quotes);
	do_test(&test_word_quotes_with_consecutive);
	do_test(&test_word_quotes_with_consecutive_and_var);
	do_test(&test_word_quotes_no_escaping);
	do_test(&test_word_dquotes);
	do_test(&test_word_dquotes_with_escaping);
	do_test(&test_word_and_token);
	print_test_result(argc, argv[0]);
	return (0);
}

static t_list	*test_tokenize(const char *str)
{
	t_tokenizer	tokenizer;
	t_list		*tokens;

	tokenizer.quote = 0;
	tokenizer.str = str;

	tokens = tokenize(&tokenizer);
	return (tokens);
}

static t_bool	validator_combined(t_token *token, va_list va)
{
	t_strbuf		strbuf;
	t_list			*wordlst;
	t_wordchunk		*chunk;
	char			*str;
	t_bool			ret;
	enum e_token	ttype;
	enum e_wordflag	wordflag;
	char			*exstr;

	ttype = va_arg(va, enum e_token);
	if (token->type != ttype)
	{
		dprintf(STDERR_FILENO, "expected tokentype:%02d (your:%02d)\n", ttype, token->type);
		return (FALSE);
	}
	if (token->type != kWord)
	{
		exstr = va_arg(va, char *);
		if (!strcmp(token->chars, exstr))
			return (TRUE);
		dprintf(STDERR_FILENO, "expected chars:{%s} (your:{%s})\n", exstr, token->chars);
		return (FALSE);
	}
	ft_memset(&strbuf, 0, sizeof(t_strbuf));
	ret = TRUE;
	wordlst = token->word->wordlist;
	while (wordlst != NULL)
	{
		chunk = wordlst->content;
		wordflag = va_arg(va, enum e_wordflag);
		exstr = va_arg(va, char *);
		if (chunk->flag != wordflag || strcmp(chunk->str, exstr))
		{
			dprintf(STDERR_FILENO, "expected wordflag:%02d (your:%02d)\n", wordflag, chunk->flag);
			dprintf(STDERR_FILENO, "expected str:{%s} (your:{%s})\n", exstr, chunk->str);
			ret = FALSE;
			break ;
		}
		if (chunk->flag == WordFlag_LastExitCode)
			strbuf_appends(&strbuf, "$?");
		if (chunk->flag == WordFlag_DollarSign)
			strbuf_append(&strbuf, '$');
		if (chunk->flag != WordFlag_LastExitCode)
			strbuf_appends(&strbuf, chunk->str);
		wordlst = wordlst->next;
	}
	str = strbuf_get(&strbuf);
	if (ret == TRUE)
	{
		exstr = va_arg(va, char *);
		if (strcmp(str, exstr))
		{
			ret = FALSE;
			dprintf(STDERR_FILENO, "expected fullstr:{%s} (your:{%s})\n", exstr, str);
		}
	}
	free(str);
	return (ret);
}

static t_bool	assert_token(const char *str, int count, ...)
{
	va_list	va;
	int		ret;
	t_list	*tokens;

	tokens = test_tokenize(str);
	if (tokens == NULL)
		return (FALSE);
	ret = kAssertFailed;
	if (ft_lstsize(tokens) == count)
	{
		ret = TRUE;
		va_start(va, count);
		for (int i = 0; i < count; i++)
		{
			if (!validator_combined(tokens->content, va))
			{
				ret = FALSE;
				break ;
			}
			tokens = tokens->next;
		}
		va_end(va);
	}
	ft_lstclear(&tokens, dispose_token);
	return (ret);
}
