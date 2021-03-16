/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:02:11 by jobenass          #+#    #+#             */
/*   Updated: 2021/03/15 00:42:28 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	ft_get_directories(char ***dirs, char **env)
{
	int		i;
	char	*start;

	i = 0;
	while (env[i] && ft_strcmp_chr(env[i], "PATH=", '=') != 0)
		i++;
	if (!env[i])
		return (EXIT_FAILURE);
	start = ft_strchr(env[i], '=');
	if (start == NULL)
		return (EXIT_FAILURE);
	start++;
	if (start[0] == '\0')
		return (EXIT_FAILURE);
	(*dirs) = ft_split(start, ':');
	if (!(*dirs))
		return (EXIT_ERROR);
	return (EXIT_SUCCESS);
}

static int	ft_get_binary(char **dirs, char **cmd)
{
	char	*tmp;
	int		ret;
	int		i;

	tmp = *cmd;
	ret = EXIT_FAILURE;
	i = -1;
	while (ret == EXIT_FAILURE && dirs && dirs[++i] && tmp[0] != '\0')
	{
		if ((*cmd = ft_join_path(dirs[i], tmp)) == NULL)
			ret = EXIT_ERROR;
		if (*cmd && (ret = ft_command_exist(*cmd)) == EXIT_SUCCESS)
			break ;
		ft_strdel(cmd);
	}
	if ((!*cmd || tmp[0] == '\0') && dirs)
		ft_error(tmp, NULL, "command not found", 0);
	if (tmp[0] == '\0')
		*cmd = NULL;
	ft_strdel(&tmp);
	return (ret);
}

static int	ft_get_absolute(char *argument, char *command, char **dirs)
{
	int		ret;

	if (!command && dirs)
		return (127);
	ret = ft_browse_path(command);
	if (errno == EACCES || errno == EISDIR)
		ret = 126;
	else if (errno == ENOENT)
		ret = 127;
	ft_error(argument, NULL, NULL, 0);
	return (ret);
}

int			ft_get_command(t_mini *shl, char **env, char **arguments, int ret)
{
	char	**dirs;

	if ((shl->psr->command = ft_strdup(*arguments)) == NULL)
		return (EXIT_ERROR);
	if (ft_is_builtins(shl->psr->command) == 1)
		return (EXIT_SUCCESS);
	ft_is_subminishell(shl->psr->command, &shl->subminishell);
	dirs = NULL;
	if (ft_strncmp(shl->psr->command, "/", 1) != 0
	&& ft_strncmp(shl->psr->command, ".", 1) != 0
	&& ft_strchr(shl->psr->command, '/') == NULL)
		if ((ret = ft_get_directories(&dirs, env)) == EXIT_SUCCESS)
			ret = ft_get_binary(dirs, &shl->psr->command);
	if (ret != EXIT_ERROR)
		ret = ft_get_absolute(*arguments, shl->psr->command, dirs);
	ft_set_others_ret(ret, NULL, shl);
	ft_tabstrdel(&dirs);
	return (ret);
}
