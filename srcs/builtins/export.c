/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninieddu <ninieddu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:01:22 by jobenass          #+#    #+#             */
/*   Updated: 2021/03/15 21:49:55 by ninieddu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	ft_add(char ***envs, char *var, char *value)
{
	char	**new;
	int		i;
	int		j;

	if (!(new = malloc(sizeof(char *) * (ft_tabstrlen(*envs) + 2))))
		return (EXIT_ERROR);
	i = 0;
	j = 0;
	while (envs && (*envs)[i] && (new[j] = ft_strdup((*envs)[i])))
	{
		i++;
		j++;
	}
	if (((*envs)[i] && new[j] == NULL) || !(new[j] = ft_strjoin(var, value)))
		ft_tabstrdel(&new);
	if (!new[j])
		return (EXIT_ERROR);
	new[++j] = NULL;
	ft_tabstrdel(envs);
	*envs = new;
	return (EXIT_SUCCESS);
}

static int	ft_update(char **env, char *var, char *value)
{
	char	*old;
	char	*new;

	old = *env;
	if (!(new = ft_strjoin(var, value)))
		return (EXIT_ERROR);
	*env = new;
	ft_strdel(&old);
	return (EXIT_SUCCESS);
}

static int	ft_get_variable(char ***envs, char *key, char *egal, char *value)
{
	char	*var;
	int		i;
	int		ret;

	if (egal != NULL)
	{
		if ((var = ft_strjoin(key, "=")) == NULL)
			return (EXIT_ERROR);
	}
	else if ((var = ft_strdup(key)) == NULL)
		return (EXIT_ERROR);
	i = -1;
	while ((*envs) && (*envs)[++i])
		if (ft_found_variable(key, (*envs)[i]))
			break ;
	ret = EXIT_SUCCESS;
	if ((*envs)[i] && egal != NULL)
		ret = ft_update(&(*envs)[i], var, value);
	else if (!(*envs)[i])
		ret = ft_add(envs, var, value);
	ft_strdel(&var);
	return (ret);
}

static int	ft_get_data(char *arg, char **key, char **egal, char **value)
{
	int		ret;

	if ((*key = ft_strdup_chr(arg, '=')) == NULL)
		return (EXIT_ERROR);
	*egal = ft_strchr(arg, '=');
	ret = EXIT_SUCCESS;
	if (*egal != NULL)
	{
		if ((*value = ft_strdup((*egal + 1))) == NULL)
			ret = EXIT_ERROR;
	}
	else if ((*value = ft_strnew(1)) == NULL)
		ret = EXIT_ERROR;
	if (ret != EXIT_SUCCESS)
		ft_strdel(key);
	return (ret);
}

int			ft_cmd_export(char **args, char ***envs, int out)
{
	char	*key;
	char	*value;
	char	*egal;
	int		ret;
	int		i;

	key = NULL;
	value = NULL;
	ret = EXIT_SUCCESS;
	if (args && args[0] && !args[1])
		ret = ft_print_environment(*envs, out);
	i = 0;
	while (ret != EXIT_ERROR && args && args[++i])
	{
		if (ft_get_data(args[i], &key, &egal, &value) == EXIT_ERROR)
			break ;
		if (ft_is_identifier(key) == EXIT_FAILURE
		&& ft_error("export", args[i], "not a valid identifier", 1) == 1)
			ret = EXIT_FAILURE;
		else if (ft_get_variable(envs, key, egal, value) == EXIT_ERROR)
			ret = EXIT_ERROR;
		ft_doublestrdel(&key, &value);
	}
	return (ret);
}
