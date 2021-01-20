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

int		ft_cmd_env(char **args, char **envs, int out)
{
	int		index;

	if (args[0] && args[1])
		return (ft_error("env", "Arguments are not permitted"));
	index = 0;
	while (envs[index])
	{
		if (ft_strchr(envs[index], '=')
		&& ft_strcmp_chr(envs[index], "?=", '=') != 0)
			ft_putendl_fd(envs[index], out);
		index++;
	}
	return (EXIT_SUCCESS);
}