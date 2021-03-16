/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninieddu <ninieddu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:03:36 by jobenass          #+#    #+#             */
/*   Updated: 2021/03/15 01:06:38 by ninieddu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int			ft_found_variable(char *key, char *env)
{
	int		val;

	val = ft_strcmp(key, env);
	if (val == -61 || val == 61 || val == 0)
		return (1);
	return (0);
}

void		ft_is_subminishell(char *command, int *subminishell)
{
	if (ft_strcmp(command, "minishell") == 0
	|| ft_strcmp(command, "./minishell") == 0)
		*subminishell = 1;
}

int			ft_is_length_data(char *data, int type)
{
	int		i;

	i = 0;
	if (type == 0)
	{
		while (data && data[i] && ft_isdigit(data[i]) == 1)
			i++;
		return (i);
	}
	else
	{
		while (data && data[i])
			i++;
		return (i);
	}
}

int			ft_is_length_environment(char **envs, int *shlvl, int *code)
{
	int		i;

	*shlvl = 0;
	*code = 0;
	i = -1;
	while (envs && envs[++i])
	{
		if (ft_found_variable(envs[i], "SHLVL") == 1)
			*shlvl = 1;
		else if (ft_found_variable(envs[i], "?") == 1)
			*code = 1;
	}
	if (*shlvl == 0)
		i++;
	if (*code == 0)
		i++;
	return (i);
}

int			ft_is_pipe(int i, t_mini *shl)
{
	while (i < shl->lxr->length)
	{
		if (ft_strcmp(shl->lxr->token[i], "|") == 0)
			return (1);
		i++;
	}
	return (0);
}
