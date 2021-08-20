/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 15:46:26 by smun              #+#    #+#             */
/*   Updated: 2021/08/20 22:40:42 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <libft.h>
# include <stdlib.h>
# include <stddef.h>
# define TRUE 1
# define FALSE 0
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
# define BLUE "\033[34m"
# define RESET "\033[0m"
# ifndef VERBOSE
#  define VERBOSE 0
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
}	t_pair;

t_bool		dict_put(t_dict *dict, char *key, char *value);
char		*dict_get(t_dict *dict, char *key);
void		dict_free(t_dict *dict);

/*
** ------------------------------------------------
**   Stack
** ------------------------------------------------
*/

typedef struct s_stack
{
	t_list	*dat;
}	t_stack;

void	*stack_peek(t_stack *stack, int index);
void	stack_push(t_stack *stack, void *data);
void	*stack_pop(t_stack *stack);
int		stack_size(t_stack *stack);

/*
** ------------------------------------------------
**   String Buffer
** ------------------------------------------------
*/

typedef struct s_strbuf
{
	t_list	*head;
}	t_strbuf;

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

void	shell_main(void);
void	shell_clean(void);

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

typedef struct	s_tokenizer
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

typedef struct	s_wordchunk
{
	enum e_wordflag	flag;
	char			*str;
}	t_wordchunk;

typedef struct	s_word
{
	t_list	*wordlist;
}	t_word;

typedef struct	s_token
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

typedef struct	s_redir
{
	enum e_redirtype	type;
	int					fd;
	int					flags;
	t_word				*filename;
	char				*heredoc_eof;
}	t_redir;

typedef struct	s_simplecmd
{
	t_list	*args;
}	t_simplecmd;

enum e_connector
{
	kPipe,
	kAnd,
	kOr
};

typedef struct	s_connect
{
	enum e_connector	connector;
	struct s_syntax		*first;
	struct s_syntax		*second;
}	t_connect;

typedef struct	s_subshell
{
	struct s_syntax		*command;
}	t_subshell;

typedef struct	s_syntax
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

t_bool		flush_wordchunk(t_word *word, t_strbuf *strbuf, t_bool final);
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
void		syntax_make_connection(t_stack *st, int type);
void		syntax_make_subshell(t_stack *st);
void		syntax_append_argument_to_simplecmd(t_stack *st);
void		syntax_append_argument_to_connect(t_stack *st);

void		dispose_wordchunk(void *ptr);
void		dispose_token(void *ptr);
void		dispose_word(void *ptr);
void		dispose_syntax(void *ptr);

/*
** ------------------------------------------------
**   Module - Run built-in or external commands.
**     cd, echo, pwd(no opt), export(no opt), unset(no opt), env, exit(no opt)
** ------------------------------------------------
*/

// void		command_run(t_command *cmd, int argc, char *argv[]);

/*
** ------------------------------------------------
**   Module - Environment
** ------------------------------------------------
*/

typedef struct s_env
{
	t_dict	env;
	t_list	*path;
}	t_env;

enum	e_printenvopt
{
	kExportNoOption,
	kEnvNoOption
};

/*
** env_put : Put an Environment data (input e.g) KEY=VALUE )
*/

void		env_put(char *value);

/*
** env_get : Get Environment value with a key
*/

char		*env_get(char *key);

/*
** env_print : Print Environment values (env, export, ...)
*/

void		env_print(int option);

/*
** env_make_envp : make char*envp[] for running the external commands
*/

char		*env_make_envp(void);

/*
** env_find_from_path : Verify if the input command can be found in saved path
**                      and returns the found path+command.
*/

char		*env_find_from_path(char *command);

/*
** ------------------------------------------------
**   Module - Context
** ------------------------------------------------
*/

typedef struct s_context
{
	t_env	env;
	char	*app_name;
	int		error;
}	t_context;

void		context_init(char *argv0);
t_context	*context_get(void);
void		print_error(const char *str);
void		exit_error(void);
char		*word_get(t_word *word, t_bool expand_vars, t_bool disposeword_after);
void		*safe_malloc(size_t size);
char		*ft_basename(char *path);

#endif
