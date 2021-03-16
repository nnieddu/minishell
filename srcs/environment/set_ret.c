/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ret.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninieddu <ninieddu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 16:20:44 by ninieddu          #+#    #+#             */
/*   Updated: 2021/03/15 15:30:16 by ninieddu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		ft_set_ret(t_mini *shl, int ret)
{
	int		i;
	char	*rett;
	char	*nbr;

	nbr = ft_itoa(ret);
	if (!(rett = ft_strjoin("?=", nbr)))
	{
		ft_strdel(&nbr);
		return (EXIT_ERROR);
	}
	i = -1;
	ft_strdel(&nbr);
	while (shl->env && shl->env[++i])
		if (ft_strncmp(shl->env[i], "?=", 2) == 0)
		{
			ft_strdel(&shl->env[i]);
			if (!(shl->env[i] = ft_strdup(rett)))
			{
				ft_strdel(&rett);
				return (EXIT_ERROR);
			}
			ft_strdel(&rett);
			break ;
		}
	return (ret);
}

int		ft_set_others_ret(int ret, char *input, t_mini *shl)
{
	if (ret == 256)
	{
		ret = 258;
		if (ft_set_ret(shl, 258) == EXIT_ERROR)
			return (EXIT_ERROR);
		if (input)
			ft_strdel(&input);
	}
	else if (ret != 0)
		if (ft_set_ret(shl, ret) == EXIT_ERROR)
			return (EXIT_ERROR);
	return (ret);
}

void	ft_set_sign_ret(t_mini *shl)
{
	if (g_pid == -2)
	{
		g_pid = -1;
		ft_set_ret(shl, 130);
	}
}
