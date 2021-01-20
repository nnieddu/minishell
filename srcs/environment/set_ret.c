/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ret.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninieddu <ninieddu@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 16:20:44 by ninieddu          #+#    #+#             */
/*   Updated: 2021/01/09 16:33:21 by ninieddu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		ft_is_first_time(t_mini *shl)
{
	int i;
	
	i = -1;
	while (shl->env && shl->env[++i])
		if (ft_strncmp(shl->env[i], "SHLVL=", 6) == 0)
			break ;
	if (ft_strcmp(shl->env[i], "SHLVL=2") == 0)
		return (1);
	return (0);
}

int		ft_set_ret(t_mini *shl, char *ret)
{
	int i;

	i = -1;
	while (shl->env && shl->env[++i])
		if (ft_strncmp(shl->env[i], "?=", 2) == 0)
		{
			free (shl->env[i]);
			shl->env[i] = ft_strdup(ret);
			break ;
		}
	return (EXIT_SUCCESS); 
}