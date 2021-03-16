/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:01:04 by jobenass          #+#    #+#             */
/*   Updated: 2021/03/02 08:39:39 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	ft_is_options(char *arg)
{
	int		i;

	i = 1;
	while (arg && arg[i] && arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		return (1);
	return (0);
}

int			ft_cmd_echo(char **args, int out)
{
	int		nonewline;
	int		index;

	nonewline = 0;
	index = 1;
	while (args[index] && ft_strncmp(args[index], "-n", 2) == 0
	&& ft_is_options(args[index]) == 1)
	{
		index++;
		nonewline = 1;
	}
	while (args && args[index])
	{
		ft_putstr_fd(args[index], out);
		if (((nonewline == 0 && index >= 1) || (nonewline == 1 && index >= 2))
		&& args[index + 1])
			ft_putchar_fd(' ', out);
		index++;
	}
	if (nonewline != 1)
		ft_putchar_fd('\n', out);
	return (EXIT_SUCCESS);
}
