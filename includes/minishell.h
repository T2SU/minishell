/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 15:46:26 by smun              #+#    #+#             */
/*   Updated: 2021/08/18 18:47:44 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <libft.h>
# include <stdlib.h>
# include <stddef.h>
# define TRUE 1
# define FALSE 0

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
	Token_Unknown,
	Token_Word,
	Token_GreaterGreater,
	Token_Greater,
	Token_Less,
	Token_LessLess,
	Token_Bar,
	Token_BarBar,
	Token_AndAnd,
	Token_Open,
	Token_Close
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
	int				type;
	struct s_word	word;
	char			chars[3];
}	t_token;

typedef struct	s_parser
{
	t_list	*lst;
	t_list	*cur;
	int		scope;
}	t_parser;

enum e_redirtype
{
	RedirectionType_None,
	RedirectionType_Write,
	RedirectionType_Append,
	RedirectionType_Read,
	RedirectionType_ReadHeredoc,
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
	t_list	*redirs;
}	t_simplecmd;

enum e_connector
{
	ConnectorType_None,
	ConnectorType_Pipe,
	ConnectorType_And,
	ConnectorType_Or
};

typedef struct	s_connect
{
	enum e_connector	connector;
	struct s_command	*first;
	struct s_command	*second;
}	t_connect;

typedef struct	s_subshell
{

}	t_subshell;

t_word	get_word(t_tokenizer *tokenizer);
t_list	*tokenize(t_tokenizer *tokenizer);

void	dispose_wordchunk(void *ptr);
void	dispose_token(void *ptr);

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

#endif
