/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:01:38 by jobenass          #+#    #+#             */
/*   Updated: 2021/03/08 18:15:55 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		ft_manage_underscore(char **envs, char **arguments)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (envs && envs[i] && ft_strcmp_chr(envs[i], "_=", '=') != 0)
		i++;
	tmp = NULL;
	if (envs[i])
	{
		j = 0;
		while (arguments && arguments[j] && arguments[j + 1])
			j++;
		if (!arguments[j])
			return (EXIT_SUCCESS);
		tmp = envs[i];
		envs[i] = ft_strjoin("_=", arguments[j]);
		ft_strdel(&tmp);
		if (!envs[i])
			return (EXIT_ERROR);
	}
	return (EXIT_SUCCESS);
}

int		ft_manage_code(char **envs, int ret)
{
	int		i;
	char	*tmp;
	char	*value;

	i = 0;
	while (envs && envs[i] && ft_strcmp_chr(envs[i], "?=", '=') != 0)
		i++;
	tmp = NULL;
	value = NULL;
	if (envs[i])
	{
		tmp = envs[i];
		if (!(value = ft_itoa(ret)))
			return (EXIT_ERROR);
		envs[i] = ft_strjoin("?=", value);
		ft_strdel(&tmp);
		ft_strdel(&value);
		if (!envs[i])
			return (EXIT_ERROR);
	}
	return (EXIT_SUCCESS);
}
