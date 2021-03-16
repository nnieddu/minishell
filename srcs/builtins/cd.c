/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:00:57 by jobenass          #+#    #+#             */
/*   Updated: 2021/03/14 17:55:02 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	ft_update_pwd_oldpwd(char **envs, char *key)
{
	int		index;
	char	*current;
	char	*var;
	char	*tmp;

	index = 0;
	while (envs[index] && ft_found_variable(key, envs[index]) == 0)
		index++;
	tmp = NULL;
	if (envs[index])
	{
		if (!(current = getcwd(NULL, 0)))
			return (EXIT_ERROR);
		var = ft_strjoin(key, "=");
		tmp = envs[index];
		if (var)
			envs[index] = ft_strjoin(var, current);
		ft_strdel(&tmp);
		ft_strdel(&current);
		if (!envs[index] || !var)
			return (EXIT_ERROR);
		ft_strdel(&var);
	}
	return (EXIT_SUCCESS);
}

static int	ft_change_dir(char *dir)
{
	DIR		*fd;

	if (dir && dir[0] != '\0')
	{
		if ((fd = opendir(dir)) == NULL)
			return (ft_error("cd", dir, NULL, 0));
		if (chdir(dir) == -1)
			return (ft_error("cd", dir, NULL, 0));
		closedir(fd);
	}
	return (EXIT_SUCCESS);
}

int			ft_cmd_cd(char **args, char **envs, int ret)
{
	int		index;
	char	*dir;

	index = 0;
	while (envs[index] && ft_strcmp_chr(envs[index], "HOME=", '=') != 0)
		index++;
	if (!envs[index])
		return (ft_error("cd", NULL, "HOME not set", 0));
	if (!args[1])
		return (ft_error("cd", NULL, "need a relative or absolute path", 0));
	dir = args[1];
	if ((ret = ft_update_pwd_oldpwd(envs, "OLDPWD")) == EXIT_ERROR
	|| (ret = ft_change_dir(dir)) == EXIT_FAILURE
	|| (ret = ft_update_pwd_oldpwd(envs, "PWD")) == EXIT_ERROR)
	{
		if (dir != args[1])
			ft_strdel(&dir);
		return (ret);
	}
	if (dir != args[1])
		ft_strdel(&dir);
	return (EXIT_SUCCESS);
}
