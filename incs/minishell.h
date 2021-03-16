/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninieddu <ninieddu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 09:14:29 by jobenass          #+#    #+#             */
/*   Updated: 2021/03/15 22:16:44 by ninieddu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>

# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/errno.h>
# include <signal.h>
# include "../srcs/libft/libft_update.h"

# define FILE 1
# define PIPE 2
# define IN 0
# define OUT 1
# define EXIT_ERROR -1

extern	pid_t			g_pid;

typedef struct			s_lexer
{
	char				*line;
	char				**subline;
	char				**token;
	int					length;
}						t_lexer;

typedef struct			s_parser
{
	int					fd[2];
	int					**mini_pipe;
	char				*command;
	char				**arguments;
}						t_parser;

typedef struct			s_list
{
	char				*content;
	struct s_list		*next;
}						t_list;

typedef struct			s_mini
{
	t_lexer				*lxr;
	t_parser			*psr;
	pid_t				pid;
	char				**env;
	char				*home;
	int					exit;
	int					subminishell;
}						t_mini;

/*
**		Lexing
*/
int						ft_lexer(t_mini *shl, char *input, int ret);
int						ft_check_quotes(char *input);
int						ft_check_tokens(t_mini *shl, char **line);
char					*ft_get_line(char *input);
char					**ft_get_subline(char *line);
char					**ft_get_token(char *subline);

/*
**		Parsing
*/
int						ft_parser(t_mini *shl, int ret, int size);
int						ft_edit_tilde(t_mini *shl, char **token);
int						ft_edit_token(char **token, char **env);

/*
**		Redirection
*/
int						ft_count_sequence(char **token);
int						**ft_set_pipes(int number);
int						ft_get_redirection(t_mini *shl, int i, int id, int ret);
int						ft_browse_redirection(char *operand, char *input);

/*
**		Execution
*/
void					ft_signal_handler(int flag);
void					ft_sign_mini(int sign);
void					ft_prompt(void);
int						ft_get_home(t_mini *shl);
void					ft_set_sign_ret(t_mini *shl);
int						ft_set_others_ret(int ret, char *input, t_mini *shl);
int						ft_lenght_conponents(t_mini *shl, char **token, int i);
int						ft_get_conponents(t_mini *shl, int size, int i);
int						ft_execute(t_mini *shl, int number, int id, int ret);
int						ft_command_exist(char *command);
int						ft_get_command(t_mini *shl, char **env\
, char **arguments, int ret);
void					ft_sort_conponents(char **arguments, int size);
int						ft_browse_path(char *input);
int						ft_execute_builtins(t_mini *shl, int out);
int						ft_execute_binaries(t_mini *shl, int in, int out\
, int id);
int						ft_end_exec(t_mini *shl, int ret, int pipe_count\
, pid_t master_pid);
int						ft_check_son_return(int status, int ret);
/*
**		Builtins
*/
int						ft_cmd_echo(char **args, int out);
int						ft_cmd_cd(char **args, char **envs, int ret);
int						ft_cmd_pwd(int out);
int						ft_cmd_export(char **args, char ***envs, int out);
int						ft_print_environment(char **envs, int out);
int						ft_cmd_unset(char **args, char ***envs);
int						ft_cmd_env(char **args, char **envs, int out);
int						ft_cmd_exit(char **args);
int						ft_exit(t_mini *shl, int ret);

/*
**		Environment
*/
int						ft_set_variables(t_mini *shl, char **envp);
int						ft_update_variables(char **envs);
int						ft_update_path(char **envs);
int						ft_update_shlvl(char **env);
int						ft_manage_underscore(char **envs, char **arguments);
int						ft_manage_code(char **envs, int err);
int						ft_set_ret(t_mini *shl, int ret);

/*
**		Commons
*/
char					*ft_get_env(char **env, char *key);
t_list					*ft_create_item(char *content);
void					ft_add_item(t_list **list, t_list *new);
int						ft_list_size(t_list *list);
void					ft_clean_list(t_list **list);
char					**ft_list_to_tab(t_list *list);

/*
**		Utils
*/
int						ft_is_quote(char *str, int index, int quote);
int						ft_is_metachar(char *str, int i);
int						ft_is_operator(char *token);
int						ft_is_separator(char *str, int i);
int						ft_is_token(char *str, int i);
int						ft_is_only_spaces(char *str);
int						ft_is_variable(char *str, int i, int quote);
int						ft_is_charset(char *str, int i);
int						ft_is_empty(char *str);
int						ft_is_escaped(char *str, int i);
int						ft_is_quoted(char *str, int i, int *quote);
int						ft_is_backslashed(char *str, int i, int quote);
int						ft_is_redirection(char *token);
int						ft_is_builtins(char *command);
int						ft_is_identifier(char *args);
void					ft_is_subminishell(char *command, int *subminishell);
int						ft_found_variable(char *key, char *envs);
char					*ft_join_path(char *dir, char *command);
int						ft_is_length_data(char *data, int type);
int						ft_is_length_environment(char **envs, int *shlvl\
, int *code);
int						ft_is_pipe(int i, t_mini *shl);
int						ft_manage_ctrld(char *input, t_mini **shl);
int						ft_get_last_ret(char *s1);
void					ft_doublestrdel(char **str1, char **str2);

/*
**		Errors
*/
int						ft_fatal_error(void);
int						ft_error(char *message, char *token, char *custom\
, int quote);
void					ft_general_clean(t_mini **shl);
void					ft_clean_lexer(t_lexer **lxr);
void					ft_clean_parser(t_parser **psr, int number, int size);

#endif
