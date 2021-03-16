/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninieddu <ninieddu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:01:13 by jobenass          #+#    #+#             */
/*   Updated: 2021/03/14 21:28:30 by ninieddu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int			ft_get_last_ret(char *s1)
{
	int		len;
	int		i;
	int		x;
	char	*dup;

	dup = 0;
	i = 2;
	x = 0;
	len = ft_strlen(s1);
	if (!(dup = (char *)ft_calloc(len + 1, sizeof(char))))
		return (EXIT_ERROR);
	while (s1[i] && i < len)
	{
		dup[x] = s1[i];
		i++;
		x++;
	}
	dup[x] = '\0';
	x = atoi(dup);
	free(dup);
	return (x);
}

int			ft_is_big_exit(char *args)
{
	char		*max;
	size_t		index;

	index = -1;
	max = "9223372036854775807";
	if (args && args[0] == '-')
	{
		max = "-9223372036854775808";
		index++;
	}
	if (args && ft_strlen(args) >= 21 + index)
		return (1);
	if (args && (ft_strlen(args) == 20 + index))
	{
		while (args[++index] && max[index])
		{
			if ((args[index] - 48) > (max[index] - 48))
				return (1);
		}
	}
	return (0);
}

static int	ft_is_exit(char **args, int index)
{
	if (args[0] && args[1] && args[2] && ft_isdigit(args[1][0]) == 1)
	{
		ft_error("exit", NULL, "too many arguments", 0);
		return (257);
	}
	if (args[1] && args[1][0] == '-')
		index++;
	if ((args[1] && (ft_isdigit(args[1][index]) == 0 || args[1][index] == 0)))
	{
		ft_error("exit", args[1], "numeric argument required", 0);
		return (255);
	}
	while (args[1] && args[1][index]
	&& (ft_isdigit(args[1][index]) == 1))
		index++;
	if ((args[1] && args[1][index]) || ft_is_big_exit(args[1]) == 1)
	{
		ft_error("exit", args[1], "numeric argument required", 0);
		return (255);
	}
	return (EXIT_SUCCESS);
}

static int	ft_manage_value(int value)
{
	if (value > 0)
		while (value > 0 && (value - 256) >= 0)
			value -= 256;
	else if (value < 0 && value > -256)
		while (value < 0 && value > -256 && (value + 256) >= 0)
			value += 256;
	else if (value < -256)
		while ((value) < 0)
			value += 256;
	return (value);
}

int			ft_cmd_exit(char **args)
{
	int		value;

	if ((value = ft_is_exit(args, 0)) != EXIT_SUCCESS)
		return (value);
	if (args[1])
	{
		value = ft_atoi(args[1]);
		value = ft_manage_value(value);
	}
	return (value);
}
