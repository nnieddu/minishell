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

static int	ft_get_access(char *command)
{
	int		find;

	find = open(command, O_RDONLY, S_IRUSR);
	if (find < 0)
		return (EXIT_FAILURE);
	close(find);
	return (EXIT_SUCCESS);
}

static char	*ft_get_binary(char **arguments, char **dirs)
{
	char	*command;
	int		i;
	
	command = NULL;
	i = -1;
	while (dirs && dirs[++i])
	{
		if ((command = ft_join_path(dirs[i], *arguments)) == NULL)
			break ;
		if (ft_get_access(command) == EXIT_SUCCESS)
			break ;
		ft_strdel(&command);
	}
	return (command);
}

static char	**ft_get_directories(char **env)
{
	int		i;
	char	*tmp;
	char	**content;

	i = 0;
	while (env[i] && ft_strcmp_chr(env[i], "PATH=", '=') != 0)
		i++;
	tmp = NULL;
	content = NULL;
	if (env[i])
	{
		tmp = ft_strchr(env[i], '=') + 1;
		if (tmp[0] == '/')
			content = ft_split(tmp, ':');
	}
	return (content);
}

char	*ft_get_command(char **env, char **arguments)
{
 	char	*command;
	char	*minishield;
	char	**dirs;

	command = NULL;
	if (ft_is_builtins(*arguments) == 1 || *arguments[0] == '/')
		return (command = ft_strdup(*arguments));
	else if (ft_strcmp(*arguments, "minishell") == 0
	|| ft_strcmp(*arguments, "./minishell") == 0)
	{
		minishield = getcwd(NULL, 0);
		command = ft_join_path(minishield, "minishell");
		ft_strdel(&minishield);
		return (command);
	}
	else
	{
		dirs = ft_get_directories(env);
		command = ft_get_binary(arguments, dirs);
		if (errno != 0)
			errno = 0;
		ft_tabstrdel(&dirs);
	}
	return (command);
}
