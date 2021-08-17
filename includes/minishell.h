/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 15:46:26 by smun              #+#    #+#             */
/*   Updated: 2021/08/17 15:25:22 by smun             ###   ########.fr       */
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
char		*strbuf_get(t_strbuf *strbuf, t_bool free_strbuf_after_get);
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
	Token_Character,
	Token_Dollar,
	Token_Read,
	Token_ReadDelim,
	Token_Write,
	Token_Append,
	Token_Quote,
	Token_Bar,
	Token_DoubleQuote,
	Token_WhiteSpace,
	Token_OpenBracket,
	Token_CloseBracket,
	Token_Or,
	Token_And
};

typedef struct	s_tokenizer
{
	const char	*str;
	int			quote;
}	t_tokenizer;

typedef struct	s_token
{
	int		type;
	char	data[3];
}	t_token;

typedef struct	s_parser
{
	t_list	*lst;
	t_list	*cur;
	int		scope;
}	t_parser;

enum e_redirectiontype
{
	RedirType_None,
	RedirType_Write,
	RedirType_Append,
	RedirType_Read,
	RedirType_ReadDelim
};

typedef struct	s_redirection
{
	int		type;
	char	*name;
}	t_redirection;

typedef struct	s_command
{
	t_list	*args;
	t_list	*redirs;
}	t_command;

typedef struct	s_job
{
	t_command		*cmd;
	struct s_job	*pipejob;
}	t_job;

enum e_statementtype
{
	StatementType_Normal,
	StatementType_Or,
	StatementType_And,
	StatementType_SingleJob
};

typedef struct	s_statement
{
	int					type;
	t_job				*job;
	struct s_statement	*first;
	struct s_statement	*second;
}	t_statement;

t_list		*tokenize(t_tokenizer *tokenizer);
void		skip_whitespaces(t_parser *parser);
int			is_acceptable(t_list *lst, int type);
char		*get_word(t_parser *parser);
char		*expand_variable(char *name);
t_command	*next_command(t_parser *parser);
void		free_command(t_command *cmd);
t_job		*next_job(t_parser *parser);
void		free_job(t_job *job);
t_statement	*next_statement(t_parser *parser);
void		free_statement(t_statement *statement);
t_statement	*parse(const char *command);
void		print_statement(t_statement *statement);

/*
** ------------------------------------------------
**   Module - Run built-in or external commands.
**     cd, echo, pwd(no opt), export(no opt), unset(no opt), env, exit(no opt)
** ------------------------------------------------
*/

void		command_run(t_command *cmd, int argc, char *argv[]);

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
