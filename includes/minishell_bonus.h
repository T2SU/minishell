/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 15:46:26 by smun              #+#    #+#             */
/*   Updated: 2021/09/19 11:03:35 by hkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H
# include <libft.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <errno.h>
# include <sys/signal.h>
# define TRUE 1
# define FALSE 0
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
# define BLUE "\033[34m"
# define RESET "\033[0m"
# define PROMPT "42$ "
# ifndef VERBOSE
#  define VERBOSE 0
# endif
# ifndef __APPLE__
#  define __APPLE__ 0
# endif

typedef int	t_bool;

/*
** ------------------------------------------------
**   Dict
** ------------------------------------------------
*/

typedef struct s_dict
{
	t_list	*head;
}	t_dict;

typedef struct s_pair
{
	char	*key;
	char	*value;
	int		equal;
}	t_pair;

t_dict		*make_dict(char **envp);
void		dict_free(t_dict *dict);
t_dict		*copy_dict(t_dict *dict);
t_dict		*sort_dict(t_dict *dict);
t_bool		dict_put(t_dict *dict, char *key, char *value, int equal);
t_bool		dict_del(t_dict *dict, char *key);
void		dict_update(t_dict *dict, char *key, char *value);
char		*dict_get(t_dict *dict, char *key);

/*
** ------------------------------------------------
**   Stack
** ------------------------------------------------
*/

typedef struct s_stack
{
	t_list	*dat;
}	t_stack;

void		*stack_peek(t_stack *stack, int index);
void		stack_push(t_stack *stack, void *data);
void		*stack_pop(t_stack *stack);
int			stack_size(t_stack *stack);

/*
** ------------------------------------------------
**   String Buffer
** ------------------------------------------------
*/

typedef struct s_strbuf
{
	t_list	*head;
	int		flag;
}	t_strbuf;

enum e_strbufflag
{
	SBFlag_None = 0,
	SBFlag_ForceFlushing = 1 << 0
};

typedef struct s_strchunk
{
	size_t	length;
	char	data[32];
}	t_strchunk;

t_bool		strbuf_append(t_strbuf *strbuf, char ch);
t_bool		strbuf_appends(t_strbuf *strbuf, const char *str);
char		*strbuf_get(t_strbuf *strbuf);
size_t		strbuf_length(t_strbuf *strbuf);

/*
** ------------------------------------------------
**   Module - Shell Prompt
** ------------------------------------------------
*/

int			retrieve_status(int status);
void		shell_sigint_handler(int sig);
void		shell_sigquit_handler(int sig);
void		shell_main(void);
void		shell_set_termattr(t_bool echoctl);
void		shell_process(char *line);

t_bool		is_exist(const char *path);
t_bool		is_dir(const char *path);

/*
** ------------------------------------------------
**   Module - Parse Syntax
** ------------------------------------------------
*/

enum e_token
{
	kUnknown,
	kWord,
	kGreaterGreater,
	kLessLess,
	kBarBar,
	kAndAnd,
	kWordList,
	kRedir,
	kSimpleCommand,
	kConnection,
	kSubShell,
	kAmpersand = '&',
	kGreater = '>',
	kLess = '<',
	kBar = '|',
	kOpen = '(',
	kClose = ')',
	kCommand
};

typedef struct s_tokenizer
{
	const char	*str;
	int			quote;
}	t_tokenizer;

enum e_wordflag
{
	WordFlag_None = 0,
	WordFlag_DollarSign = 1 << 0,
	WordFlag_LastExitCode = 1 << 1
};

typedef struct s_wordchunk
{
	enum e_wordflag	flag;
	char			*str;
	int				quote;
}	t_wordchunk;

typedef struct s_word
{
	t_list	*wordlist;
}	t_word;

typedef struct s_token
{
	enum e_token	type;
	struct s_word	*word;
	char			chars[3];
}	t_token;

enum e_redirtype
{
	kWrite,
	kAppend,
	kRead,
	kReadHeredoc,
};

typedef struct s_redir
{
	enum e_redirtype	type;
	int					flags;
	t_word				*filename;
	char				*heredoc_eof;
	char				*heredoc_file;
}	t_redir;

typedef struct s_simplecmd
{
	t_list	*args;
}	t_simplecmd;

enum e_connector
{
	kPipe,
	kAnd,
	kOr
};

typedef struct s_connect
{
	enum e_connector	connector;
	struct s_syntax		*first;
	struct s_syntax		*second;
}	t_connect;

typedef struct s_subshell
{
	struct s_syntax		*command;
}	t_subshell;

typedef struct s_syntax
{
	enum e_token		type;
	struct s_simplecmd	*simplecmd;
	struct s_connect	*connect;
	struct s_subshell	*subshell;
	struct s_word		*word;
	t_list				*wordlist;
	t_list				*redirs;
}	t_syntax;

enum e_parsestatus
{
	kSuccess,
	kEmptyLine,
	kFailed
};

int			parse(t_syntax **syntax, char *line);

t_bool		flush_chunk(t_word *word, t_strbuf *strbuf,
				t_tokenizer *t, t_bool final);
t_word		*dup_word(t_word *ref);
t_word		*get_word(t_tokenizer *tokenizer);
t_list		*tokenize(t_tokenizer *tokenizer);
void		print_tokens(t_list *tokens);

t_syntax	*syntax_parse(t_list *tokens);
t_syntax	*syntax_make(void *data, enum e_token desired_type);
void		*syntax_strip(t_syntax *syntax, enum e_token desired_type);
t_bool		syntax_is_command(t_syntax *syntax);
void		syntax_print(t_syntax *syntax);

t_bool		syntax_assemble(t_stack *st);
t_bool		syntax_reassemble(t_stack *st);
void		syntax_build_from_token(t_stack *st, t_token *token);
void		syntax_make_wordlist(t_stack *st, t_syntax *syntax);
void		syntax_make_redirection(t_stack *st, int type);
void		syntax_make_redirections(t_stack *st, t_syntax *next);
void		syntax_make_simplecmd(t_stack *st);
void		syntax_connect_redirection(t_stack *st, t_syntax *redir);
void		syntax_connect_redirection_reverse(t_stack *st, t_syntax *command);
void		syntax_make_connection(t_stack *st, int type);
void		syntax_make_subshell(t_stack *st);
void		syntax_append_argument_to_simplecmd(t_stack *st);
void		syntax_append_argument_to_connect(t_stack *st);
void		syntax_separate_bond_connect(t_stack *st);

void		dispose_wordchunk(void *ptr);
void		dispose_token(void *ptr);
void		dispose_word(void *ptr);
void		dispose_syntax(void *ptr);

/*
** ------------------------------------------------
**   Module - Execution
** ------------------------------------------------
*/

/*
** syntax:  Command Syntax Structure
** fd_in:   File Descriptor STDIN
** heredoc: Temporary heredoc file path (malloc-ed)
** fd_out:  File Descriptor STDOUT
** pid:     Child Process Id
** status:  Exit Code (Status Code)
*/

typedef struct s_filedes
{
	int	fd;
	int	stdfd;
}	t_filedes;

typedef struct s_execution
{
	t_syntax	*syntax;
	t_filedes	in;
	t_filedes	out;
	char		*heredoc;
}	t_execution;

typedef struct s_input
{
	int		argc;
	char	**argv;
	char	**envp;
}	t_input;

enum e_redirflag
{
	kFileIn = 1 << 0,
	kFileOut = 1 << 1
};

t_bool		execution_handle_redirections(t_execution *exec);
char		*execution_make_heredoc(t_redir *redir);
t_bool		execution_prepare_heredoc(t_syntax *syntax);
void		execution_install_redir(t_execution *exec, t_bool enable);
t_bool		execution_set_redir(t_execution *exec, int flags, int fd);

void		free_char_arrays(char *argv[]);
int			execution_start(t_syntax *syntax);
int			execution_simplecmd_run(t_simplecmd *scmd);
int			execution_connect_run(t_connect *con);
int			execution_subshell_run(t_subshell *subshell);

/*
** ------------------------------------------------
**   Module - Run built-in or external commands.
**     cd, echo, pwd(no opt), export(no opt), unset(no opt), env, exit(no opt)
** ------------------------------------------------
*/

t_bool		is_same_word(const char *str1, const char *str2);
t_bool		is_command(const char *cmd);
t_bool		is_builtin(const char *cmd);
char		*is_path_command(const char *cmd, t_dict *dict);
t_bool		has_path_variable(t_dict *dict);
t_bool		is_valid_name(char *str);
int			command_run_builtin(int argc, char *argv[], t_dict *dict);
int			command_run_echo(int argc, char *argv[], t_dict *dict);
int			command_run_cd(int argc, char *argv[], t_dict *dict);
int			command_run_pwd(int argc, char *argv[], t_dict *dict);
int			command_run_export(int argc, char *argv[], t_dict *dict);
int			command_run_env(int argc, char *argv[], t_dict *dict);
int			command_run_unset(int argc, char *argv[], t_dict *dict);
int			command_run_exit(int argc, char *argv[], t_dict *dict);

void		compare_and_swap(t_list	*lst);
t_dict		*sort_dict(t_dict *dict);
int			find_equal(char *str);
void		print_export(void *content);

enum e_proc
{
	kInChildProc = 1 << 0,
	kInSubShell = 1 << 1,
	kThrowed = 1 << 2
};

typedef struct s_context
{
	t_dict	*env;
	char	*app_name;
	int		flag;
	int		error;
	t_bool	heredoc;
	t_bool	interactive;
	int		laststatus;
}	t_context;

void		context_init(char *argv[], char *envp[]);
t_context	*context_get(void);
t_bool		context_has_flag(int flag);
void		context_set_child(void);
void		context_print_strsignal(int status);
t_bool		context_is_signaled(int status);
t_bool		context_is_exited(int status);
t_bool		context_get_exit_status(int status);
int			context_get_signal_num(int status);
int			context_exitcode(int code, int sig);

int			context_delisig_execution(t_syntax *syntax);
int			context_delisig_process(int *pstatus);

t_bool		print_error(const char *app, const char *why, const char *desc);
void		exit_error(void);
t_bool		raise_system_error(const char *why);
t_bool		raise_error(const char *why, const char *desc);
t_bool		raise_arg_error(const char *why, const char *arg, const char *desc);
t_bool		raise_arg_err_quote(const char *why, const char *arg,
				const char *desc);
t_bool		print_arg_error(const char *app, const char *why, const char *arg,
				const char *desc);
t_bool		raise_system_arg_error(const char *why, const char *arg);

char		*expand_variable(t_wordchunk *chunk);
t_bool		is_single_dollar_sign(t_word *word);
char		*word_get(t_word *word, t_bool expand_vars,
				t_bool disposeword_after);
void		insert_to_list(char *str, t_list **lst);
void		word_get_as_list(t_word *word, t_list **lst);
t_bool		is_wildcard(t_word *word);
void		expand_wildcard(t_list **input);
char		*get_single_filename(t_word *word);
t_bool		is_ambiguous_redirect(t_word *word);
char		**parse_arguments(t_simplecmd *scmd, int *argc);

enum		e_convert_type
{
	kArgument,
	kEnvironment
};

char		**convert_to_array(t_list *input, enum e_convert_type type);
int			get_vector_size(void *vector);

enum e_order
{
	kAscending,
	kDescending
};

void		ft_lstsort(t_list *input, enum e_order order);

char		*safe_strdup(char *str);
void		*safe_malloc(size_t size);
char		*ft_basename(char *path);
t_bool		ft_randomstr(char *buffer, size_t len);
char		*ft_strsignal(int signal);

#endif
