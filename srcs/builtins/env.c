/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:01:09 by jobenass          #+#    #+#             */
/*   Updated: 2021/03/03 11:07:48 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		ft_cmd_env(char **args, char **envs, int out)
{
	int		index;

	if (args[0] && args[1])
		return (ft_error("env", NULL, "arguments are not permitted", 0));
	index = 0;
	while (envs[index])
	{
		if (ft_strchr(envs[index], '=')
		&& ft_strncmp(envs[index], "?=", 2) != 0)
			ft_putendl_fd(envs[index], out);
		index++;
	}
	return (EXIT_SUCCESS);
}
