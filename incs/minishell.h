#ifndef MINISHELL_H
# define MINISHELL_H

////////////////////////////////////////////////////////////////////////////////
// JUST FOR TESTS
# define BLUE "\x1B[1;34m"
# define GREEN "\x1B[1;32m"
# define RED "\x1B[1;31m"
# define YELLOW "\x1B[1;33m"
# define PURPLE "\x1B[1;35m"
# define WHITE "\x1B[0;37m"
# define ENDCOLOR "\x1B[0m"
////////////////////////////////////////////////////////////////////////////////

# include "../srcs/libft/libft_update.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/errno.h>

# define IN 0
# define OUT 1

# define EXIT_ERROR -1

pid_t	pid;

typedef struct			s_lexer
{
	char				*line;
	char				**subline;
	char				**token;
}						t_lexer;

typedef struct			s_parser
{
	int					fd[2];
	int					**tube;
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
	char				**env;
	int					crash;
	int					exit;
}						t_mini;

/*
**		Lexing
*/
int		ft_lexer(t_mini *shl, char *input, int ret);
int		ft_check_syntax(char *input);
char 	*ft_get_line(char *input);
char	**ft_get_subline(char *line);
char	**ft_get_token(char *subline);

/*
**		Parsing
*/
int		ft_parser(t_mini *shl, int ret);
int		ft_edit_variable(t_mini *shl, char **token);
int		ft_edit_token(char **token);

/*
**		Redirection
*/
int		ft_count_sequence(char **token);
int		**ft_set_pipes(int number);
int		ft_get_redirection(t_mini *shl, int i, int id);
int		ft_browse_redirection(char *operand, char *input);

/*
**		Execution
*/
void	ft_signal_handler(int flag);
void	ft_sign_mini(int sign);
void	ft_prompt(void);

int		ft_get_conponents(char **token, char ***arguments, int *i);
int		ft_executer(t_mini *shl, int number, int id, int err);
int		ft_execute_builtins(t_mini *shl, int out);
char	*ft_get_command(char **env, char **arguments);
int		ft_execute_binaries(t_mini *shl, int in, int out);

/*
**		Builtins
*/
int		ft_cmd_echo(char **args, int out);
int		ft_cmd_cd(char **args, char **envs);
int		ft_cmd_pwd(int out);
// int		ft_cmd_export(char **args, char ***envs);
int		ft_cmd_unset(char **args, char ***envs);
int		ft_cmd_env(char **args, char **envs, int out);
int		ft_cmd_exit(char **args);
int		ft_exit(t_mini *shl, int ret);

/*
**		Environment
*/
char	*ft_manage_shlvl(char *shlvl);
int		ft_manage_underscore(char **envs, char **arguments);
int		ft_manage_code(char **envs, int err);
int		ft_set_ret(t_mini *shl, char *ret);


/*
**		Commons
*/
char	*ft_get_env(char **env, char *key);

t_list	*ft_create_item(char *content);
void	ft_add_item(t_list **list, t_list *new);
int		ft_list_size(t_list *list);
void	ft_clean_list(t_list **list);
char	**ft_list_to_tab(t_list *list);

/*
**		Utils
*/
int		ft_is_quote(char *str, int index, int quote);
int		ft_is_metachar(char *str, int i);
int		ft_is_separator(char *str, int i);
int		ft_is_token(int c);
int		ft_is_only_spaces(char *str);
int		ft_is_variable(char *str, int i, int quote);
int		ft_is_charset(char *str, int i);
int		ft_need_expand(char *str);
int		ft_is_builtins(char *command);
char	*ft_join_path(char *dir, char *command);
int		ft_is_first_time(t_mini *shl);

/*
**		Errors
*/
int		ft_error(char *message, char *custom);
void	ft_crash(t_mini **shl, t_list **list, int number);
void	ft_clean_general(t_mini **shl);
void	ft_clean_lexer(t_lexer **lxr);
void	ft_clean_parser(t_parser **psr, int number);

#endif