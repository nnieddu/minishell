/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:03:32 by jobenass          #+#    #+#             */
/*   Updated: 2021/03/12 12:22:37 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		ft_fatal_error(void)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("Has encountered an error and must stop", STDERR_FILENO);
	ft_putendl_fd(" ¯\\_(ツ)_/¯ ", STDERR_FILENO);
	return (EXIT_ERROR);
}

int		ft_error(char *message, char *token, char *custom, int quote)
{
	if ((errno != 0 || custom != NULL))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(message, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		if (token)
		{
			if (quote == 1)
				ft_putstr_fd("`", STDERR_FILENO);
			ft_putstr_fd(token, STDERR_FILENO);
			if (quote == 1)
				ft_putstr_fd("\'", STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
		}
		if (custom != NULL)
			ft_putendl_fd(custom, STDERR_FILENO);
		else if (errno != 0)
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
		errno = 0;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int		ft_manage_ctrld(char *input, t_mini **shl)
{
	int ret;
	int i;

	i = -1;
	ft_putendl_fd("exit", 2);
	while ((*shl)->env && (*shl)->env[++i])
		if (ft_strncmp((*shl)->env[i], "?=", 2) == 0)
			ret = ft_get_last_ret((*shl)->env[i]);
	if (input)
		ft_strdel(&input);
	ft_general_clean(shl);
	return (ret);
}
