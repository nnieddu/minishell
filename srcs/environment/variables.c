/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninieddu <ninieddu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:03:17 by jobenass          #+#    #+#             */
/*   Updated: 2021/03/10 15:49:39 by ninieddu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		ft_update_shlvl(char **env)
{
	char	*data;
	char	*tmp1;
	int		value;
	char	*tmp2;

	if ((data = ft_strchr(*env, '=')) != NULL)
		data++;
	tmp1 = *env;
	if ((ft_is_length_data(data, 1) != ft_is_length_data(data, 0)
	|| data == NULL) && (*env = strdup("SHLVL=1")) != NULL)
	{
		ft_strdel(&tmp1);
		return (EXIT_SUCCESS);
	}
	if (tmp1 && !*env)
		return (EXIT_ERROR);
	value = ft_atoi(data) + 1;
	if (!(tmp2 = ft_itoa(value)))
		return (EXIT_ERROR);
	*env = ft_strjoin("SHLVL=", tmp2);
	ft_strdel(&tmp1);
	ft_strdel(&tmp2);
	if (!*env)
		return (EXIT_ERROR);
	return (EXIT_SUCCESS);
}

int		ft_update_path(char **env)
{
	char	*value;
	char	*tmp1;
	char	*tmp2;
	int		ret;

	tmp1 = *env;
	if (!(value = getcwd(NULL, 0)))
		return (EXIT_ERROR);
	ret = EXIT_SUCCESS;
	if (!(tmp2 = ft_strjoin(":", value))
	|| !(*env = ft_strjoin(tmp1, tmp2)))
		ret = EXIT_ERROR;
	if (*env != NULL)
		ft_strdel(&tmp1);
	else
		*env = tmp1;
	ft_strdel(&value);
	ft_strdel(&tmp2);
	return (ret);
}

int		ft_update_variables(char **envs)
{
	int		index;
	int		ret;

	ret = EXIT_SUCCESS;
	index = -1;
	while (ret != EXIT_ERROR && envs && envs[++index])
	{
		if (ft_found_variable("SHLVL", envs[index]) == 1)
			ret = ft_update_shlvl(&envs[index]);
		else if (ft_strcmp_chr(envs[index], "PATH=", '=') == 0)
			ret = ft_update_path(&envs[index]);
	}
	return (ret);
}

int		ft_set_variables(t_mini *shl, char **envp)
{
	int		shlvl;
	int		code;
	int		i;

	if (!(shl->env = malloc(sizeof(char *) \
	* (ft_is_length_environment(envp, &shlvl, &code) + 1))))
		return (EXIT_ERROR);
	i = -1;
	while (envp && envp[++i])
	{
		if (ft_found_variable("OLDPWD", envp[i]) == 1)
			shl->env[i] = ft_strdup("OLDPWD");
		else if (ft_found_variable("?", envp[i]) == 1)
			shl->env[i] = ft_strdup("?=0");
		else
			shl->env[i] = ft_strdup(envp[i]);
		if (!shl->env[i])
			return (EXIT_ERROR);
	}
	if (shlvl == 0 && !(shl->env[i++] = ft_strdup("SHLVL")))
		return (EXIT_ERROR);
	if (code == 0 && !(shl->env[i++] = ft_strjoin("?=", "0")))
		return (EXIT_ERROR);
	shl->env[i] = NULL;
	return (EXIT_SUCCESS);
}
