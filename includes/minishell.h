/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 15:46:26 by smun              #+#    #+#             */
/*   Updated: 2021/08/15 17:40:14 by smun             ###   ########.fr       */
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

typedef struct	s_syntax
{

}	t_syntax;

t_syntax	*syntax_parse(const char *command);

/*
** ------------------------------------------------
**   Module - Utilize Command
** ------------------------------------------------
*/

void	process_run(t_syntax *syntax);
void	process_exec_pipe(t_syntax *syntax);
void	process_exec_cmd(t_syntax *syntax);

/*
** ------------------------------------------------
**   Module - I/O (|, >, >>, <, <<)
** ------------------------------------------------
*/

typedef struct s_command
{
	char	*redir_in;
	char	*redir_out;
	int		pipe_in;
	int		pipe_out;
}	t_command;

void		io_prepare(t_command *cmd);
void		io_clean(t_command *cmd);

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
}	t_context;

void		context_init(char *argv0);
t_context	*context_get(void);

#endif
