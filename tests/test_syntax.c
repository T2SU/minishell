/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 18:03:24 by smun              #+#    #+#             */
/*   Updated: 2021/08/21 21:33:31 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testlib.h"
#include "minishell.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

static t_bool	assert_syntax(char *str, ...);

static void	test_simplecmd_single_arg(void)
{
	assert(assert_syntax("echo",
		kSimpleCommand,
			1,
				"echo",
			0
	));
}

static void	test_simplecmd_args(void)
{
	assert(assert_syntax("  echo  hello    world            ",
		kSimpleCommand,
			3,
				"echo",
				"hello",
				"world",
			0
	));
}

static void	test_simplecmd_args2(void)
{
	assert(assert_syntax("  echo \"hello  world !!!\"           ",
		kSimpleCommand,
			2,
				"echo",
				"hello  world !!!",
			0
	));
}

static void	test_simplecmd_redir(void)
{
	assert(assert_syntax("echo 'hello world' > filename.txt",
		kSimpleCommand,
			2,
				"echo",
				"hello world",
			1,
				kWrite, "filename.txt"
	));
}

static void	test_simplecmd_redirs(void)
{
	assert(assert_syntax("echo 'hello world' > filename.txt << heredoc i love 42seoul > filename2.txt ':)' < infile.txt minishell!! >> append.txt",
		kSimpleCommand,
			7,
				"echo",
				"hello world",
				"i",
				"love",
				"42seoul",
				":)",
				"minishell!!",
			5,
				kWrite, "filename.txt",
				kReadHeredoc, "heredoc",
				kWrite, "filename2.txt",
				kRead, "infile.txt",
				kAppend, "append.txt"
	));
}

static void	test_pipe_simplecmds(void)
{
	assert(assert_syntax("echo hello world | cat",
		kConnection,
			kSimpleCommand,
				3,
					"echo",
					"hello",
					"world",
				0,
			'|',
			kSimpleCommand,
				1,
					"cat",
				0,
			0
	));
}

static void	test_pipe_simplecmds_with_redirection(void)
{
	assert(assert_syntax("echo hello world < goto \"42seoul :)\" | cat > filename.txt dd",
		kConnection,
			kSimpleCommand,
				4,
					"echo",
					"hello",
					"world",
					"42seoul :)",
				1,
					kRead, "goto",
			'|',
			kSimpleCommand,
				2,
					"cat",
					"dd",
				0,
			1,
				kWrite, "filename.txt"
	));
}

static void	test_consecutive_pipes(void)
{
	assert(assert_syntax("echo hello|cat |world hello|42seoul",
		kConnection,
			kConnection,
				kConnection,
					kSimpleCommand,
						2,
							"echo",
							"hello",
						0,
					'|',
					kSimpleCommand,
						1,
							"cat",
						0,
					0,
				'|',
				kSimpleCommand,
					2,
						"world",
						"hello",
					0,
				0,
			'|',
			kSimpleCommand,
				1,
					"42seoul",
				0,
			0
	));
}

static void	test_consecutive_pipes_with_redirections(void)
{
	assert(assert_syntax("echo > hello.txt < gogo << EOF hello|cat > test.txt |world hello|42seoul >> append.txt",
		kConnection,
			kConnection,
				kConnection,
					kSimpleCommand,
						2,
							"echo",
							"hello",
						3,
							kWrite, "hello.txt",
							kRead, "gogo",
							kReadHeredoc, "EOF",
					'|',
					kSimpleCommand,
						1,
							"cat",
						0,
					1,
						kWrite, "test.txt",
				'|',
				kSimpleCommand,
					2,
						"world",
						"hello",
					0,
				0,
			'|',
			kSimpleCommand,
				1,
					"42seoul",
				0,
			1,
				kAppend, "append.txt"
	));
}

static void	test_connection_and(void)
{
	assert(assert_syntax("echo hello world && cat < filename.txt && hexdump -C << EOF",
		kConnection,
			kConnection,
				kSimpleCommand,
					3,
						"echo",
						"hello",
						"world",
					0,
				kAndAnd,
				kSimpleCommand,
					1,
						"cat",
					0,
				1,
					kRead, "filename.txt",
			kAndAnd,
			kSimpleCommand,
				2,
					"hexdump",
					"-C",
				0,
			1,
				kReadHeredoc, "EOF"
	));
}

static void	test_connection_and_or(void)
{
	assert(assert_syntax("echo hello world && cat||cat < filename.txt && hexdump -C << EOF",
		kConnection,
			kConnection,
				kConnection,
					kSimpleCommand,
						3,
							"echo",
							"hello",
							"world",
						0,
					kAndAnd,
					kSimpleCommand,
						1,
							"cat",
						0,
					0,
				kBarBar,
				kSimpleCommand,
					1,
						"cat",
					0,
				1,
					kRead, "filename.txt",
			kAndAnd,
			kSimpleCommand,
				2,
					"hexdump",
					"-C",
				0,
			1,
				kReadHeredoc, "EOF"
	));
}

static void	test_subshell_simple(void)
{
	assert(assert_syntax("(echo hello && pwd) > filename1.txt || (cat -e < filename2.txt)",
		kConnection,
			kSubShell,
				kConnection,
					kSimpleCommand,
						2,
							"echo",
							"hello",
						0,
					kAndAnd,
					kSimpleCommand,
						1,
							"pwd",
						0,
					0,
				1,
					kWrite, "filename1.txt",
			kBarBar,
			kSubShell,
				kSimpleCommand,
					2,
						"cat",
						"-e",
					1,
						kRead, "filename2.txt",
				0,
			0
	));
}

static void	test_subshell_nested(void)
{
	assert(assert_syntax("((echo hello && (pwd)) > filename1.txt) || exit",
		kConnection,
			kSubShell,
				kSubShell,
					kConnection,
						kSimpleCommand,
							2,
								"echo",
								"hello",
							0,
						kAndAnd,
						kSubShell,
							kSimpleCommand,
								1,
									"pwd",
								0,
							0,
						0,
					1,
						kWrite, "filename1.txt",
				0,
			kBarBar,
			kSimpleCommand,
				1,
					"exit",
				0,
			0
	));
}


int		main(int argc, char *argv[])
{
	do_test(&test_simplecmd_single_arg);
	do_test(&test_simplecmd_args);
	do_test(&test_simplecmd_args2);
	do_test(&test_simplecmd_redir);
	do_test(&test_simplecmd_redirs);
	do_test(&test_pipe_simplecmds);
	do_test(&test_pipe_simplecmds_with_redirection);
	do_test(&test_consecutive_pipes);
	do_test(&test_consecutive_pipes_with_redirections);
	do_test(&test_connection_and);
	do_test(&test_connection_and_or);
	do_test(&test_subshell_simple);
	do_test(&test_subshell_nested);
	print_test_result(argc, argv[0]);
	return (0);
}

static t_bool	assert_chars(char *str, va_list *ap)
{
	t_bool	ret;
	char	*exstr;

	exstr = va_arg(*ap, char*);
	ret = !strcmp(str, exstr);
	if (!ret)
		dprintf(STDERR_FILENO, "expected wordstr:{%s} (your:{%s})\n", exstr, str);
	return (ret);
}

static t_bool	assert_word(t_word *word, va_list *ap)
{
	char	*str;
	t_bool	ret;

	str = word_get(word, FALSE, FALSE);
	ret = assert_chars(str, ap);
	free(str);
	return (ret);
}

static t_bool	assert_redir(t_redir *redir, va_list *ap)
{
	enum e_redirtype	redirtype;

	redirtype = va_arg(*ap, enum e_redirtype);
	if (redirtype != redir->type)
	{
		dprintf(STDERR_FILENO, "expected redirtype:%02d (your:%02d)\n", redirtype, redir->type);
		return (FALSE);
	}
	switch (redir->type)
	{
		case kRead:
		case kWrite:
		case kAppend:
			return (assert_word(redir->filename, ap));
		case kReadHeredoc:
			return (assert_chars(redir->heredoc_eof, ap));
	}
	return (FALSE);
}

static t_bool	assert_syntax_va(t_syntax *syntax, va_list *ap)
{
	t_list	*lst;
	int		exargcount;
	enum e_token		extype;
	enum e_connector	contype;

	extype = va_arg(*ap, enum e_token);
	if (syntax->type != extype)
	{
		dprintf(STDERR_FILENO, "expected syntaxtype:%02d (your:%02d)\n", extype, syntax->type);
		return (FALSE);
	}
	switch (syntax->type)
	{
		case kWord:
			return (assert_word(syntax->word, ap));
		case kWordList:
			lst = syntax->wordlist;
			goto Test_Wordlist;
		case kSimpleCommand:
			lst = syntax->simplecmd->args;
		Test_Wordlist:
			exargcount = va_arg(*ap, int);
			if (exargcount != ft_lstsize(lst))
			{
				dprintf(STDERR_FILENO, "expected args count:%02d (your:%02d)\n", exargcount, ft_lstsize(lst));
				return (FALSE);
			}
			while (lst != NULL)
			{
				if (!assert_word(lst->content, ap))
					return (FALSE);
				lst = lst->next;
			}
			break;
		case kConnection:
			if (!assert_syntax_va(syntax->connect->first, ap))
				return (FALSE);
			contype = va_arg(*ap, enum e_connector);
			if (contype == syntax->connect->connector)
			{
				dprintf(STDERR_FILENO, "expected connectortype:%02d (your:%02d)\n", contype, syntax->connect->connector);
				return (FALSE);
			}
			if (!assert_syntax_va(syntax->connect->second, ap))
				return (FALSE);
			break;
		case kSubShell:
			if (!assert_syntax_va(syntax->subshell->command, ap))
				return (FALSE);
			break;
		default:
			return (TRUE);
	}
	exargcount = va_arg(*ap, int);
	lst = syntax->redirs;
	if (ft_lstsize(lst) != exargcount)
	{
		dprintf(STDERR_FILENO, "expected redirs count:%02d (your:%02d)\n", exargcount, ft_lstsize(lst));
		return (FALSE);
	}
	while (lst != NULL)
	{
		if (!assert_redir(lst->content, ap))
			return (FALSE);
		lst = lst->next;
	}
	return (TRUE);
}

static t_bool	assert_syntax(char *str, ...)
{
	t_syntax	*syntax;
	va_list		va;
	t_bool		ret;

	parse(&syntax, str);
	if (syntax == NULL)
		return (FALSE);
	va_start(va, str);
	ret = assert_syntax_va(syntax, &va);
	va_end(va);
	dispose_syntax(syntax);
	if (!assert_leaks())
		ret = FALSE;
	return (ret);
}
