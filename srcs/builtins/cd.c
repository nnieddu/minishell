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

static int	ft_manage_pwd_oldpwd(char **envs, char *key)
{
	int		index;
	char	*current;
	char	*tmp;

	index = 0;
	while (envs[index] && ft_strcmp_chr(envs[index], key, '=') != 0)
		index++;
	tmp = 0;
	if (envs[index])
	{
		if (!(current = getcwd(NULL, 0)))
			return (EXIT_FAILURE);
		tmp = envs[index];
		envs[index] = ft_strjoin(key, current);
		ft_strdel(&tmp);
		ft_strdel(&current);
		if (!envs[index])
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ft_change_dir(char *dir, char *home)
{
	if (dir && (chdir(dir) == -1))
		return (ft_error("cd", NULL));
	else if (!dir && !home)
		return (ft_error("cd", "HOME not set"));
	return (EXIT_SUCCESS);
}

int			ft_cmd_cd(char **args, char **envs)
{
	int		index;
	char	*dir;

	index = 0;
	while (envs[index] && ft_strcmp_chr(envs[index], "HOME", '=') != 0)
		index++;
	dir = args[1];
	if (ft_manage_pwd_oldpwd(envs, "OLDPWD=") == EXIT_FAILURE
	|| ft_change_dir(dir, envs[index]) == EXIT_FAILURE
	|| ft_manage_pwd_oldpwd(envs, "PWD=") == EXIT_FAILURE)
	{
		if (dir != args[1])
			ft_strdel(&dir);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
