/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:01:31 by jobenass          #+#    #+#             */
/*   Updated: 2021/03/02 12:35:25 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static char	**ft_rebuild_variables(char *var, char **envs)
{
	int		size;
	int		in;
	int		out;
	char	**new;

	size = 0;
	while (envs[size])
		size++;
	if (!(new = malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	in = 0;
	out = 0;
	while (envs[in])
	{
		if (ft_found_variable(var, envs[in]) == 0
		&& !(new[out++] = ft_strdup(envs[in])))
		{
			ft_tabstrdel(&new);
			break ;
		}
		in++;
	}
	if (new)
		new[out] = NULL;
	return (new);
}

static int	ft_delete(char *key, char ***envs)
{
	int		index;
	char	**new;

	index = -1;
	while ((*envs)[++index])
		if (ft_found_variable(key, (*envs)[index]) == 1)
			break ;
	new = NULL;
	if ((*envs)[index])
	{
		new = ft_rebuild_variables(key, *envs);
		if (!new)
			return (EXIT_ERROR);
		ft_tabstrdel(envs);
		*envs = new;
	}
	return (*envs != NULL ? EXIT_SUCCESS : EXIT_FAILURE);
}

int			ft_cmd_unset(char **args, char ***envs)
{
	int		index;
	int		ret;

	index = 1;
	ret = EXIT_SUCCESS;
	while (args[index])
	{
		if (ft_is_identifier(args[index]) == EXIT_SUCCESS)
		{
			if (ft_delete(args[index], envs) == EXIT_ERROR)
				return (EXIT_ERROR);
		}
		else
			ret = ft_error("unset", args[index], "not a valid identifier", 1);
		index++;
	}
	return (ret);
}
