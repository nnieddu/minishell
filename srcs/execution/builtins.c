////////////////////////////////////////////////////////////////////////////////
//
// 		███    ██  ██████  ████████ ███████ ███████ 
// 		████   ██ ██    ██    ██    ██      ██      
// 		██ ██  ██ ██    ██    ██    █████   ███████ 
// 		██  ██ ██ ██    ██    ██    ██           ██ 
// 		██   ████  ██████     ██    ███████ ███████ 
//
////////////////////////////////////////////////////////////////////////////////

#include "../../incs/minishell.h"

int		ft_is_builtins(char *command)
{
	if (ft_strcmp(command, "echo") == 0
	|| ft_strcmp(command, "cd") == 0
	|| ft_strcmp(command, "pwd") == 0
	|| ft_strcmp(command, "export") == 0
	|| ft_strcmp(command, "unset") == 0
	|| ft_strcmp(command, "env") == 0
	|| ft_strcmp(command, "exit") == 0)
		return (1);
	return (0);
}

int		ft_execute_builtins(t_mini *shl, int out)
{
	int		ret;

	ret = 0;
	if (ft_strcmp(shl->psr->command, "echo") == 0)
		ret = ft_cmd_echo(shl->psr->arguments, out);
	else if (ft_strcmp(shl->psr->command, "cd") == 0)
		ret = ft_cmd_cd(shl->psr->arguments, shl->env);
	else if (ft_strcmp(shl->psr->command, "pwd") == 0)
		ret = ft_cmd_pwd(out);
	// else if (ft_strcmp(shl->psr->command, "export") == 0)
	// 	ret = ft_cmd_export(shl->psr->arguments, &shl->env);
	else if (ft_strcmp(shl->psr->command, "unset") == 0)
		ret = ft_cmd_unset(shl->psr->arguments, &shl->env);
	else if (ft_strcmp(shl->psr->command, "env") == 0)
		ret = ft_cmd_env(shl->psr->arguments, shl->env, out);
	else if (ft_strcmp(shl->psr->command, "exit") == 0)
	{
		ret = ft_cmd_exit(shl->psr->arguments);
		ret = ft_exit(shl, ret);
	}
	if (out != STDOUT_FILENO)
		close(out);
	return (ret);
}