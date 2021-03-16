/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:01:44 by jobenass          #+#    #+#             */
/*   Updated: 2021/03/05 11:34:05 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		ft_get_home(t_mini *shl)
{
	char	*path;
	int		slash;
	int		i;

	if (!(path = getcwd(NULL, 0)))
		return (EXIT_ERROR);
	slash = 0;
	i = -1;
	while (path && path[++i])
	{
		if (path[i] == '/')
			slash++;
		if (slash == 3)
			break ;
	}
	shl->home = ft_strdup_idx(path, i);
	ft_strdel(&path);
	if (shl->home == NULL)
		return (EXIT_ERROR);
	return (EXIT_SUCCESS);
}
