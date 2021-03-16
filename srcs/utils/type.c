/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninieddu <ninieddu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:03:36 by jobenass          #+#    #+#             */
/*   Updated: 2021/03/14 12:41:36 by ninieddu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		ft_is_identifier(char *args)
{
	int		index;

	index = 0;
	if (ft_isdigit(args[0]) == 1 || args[0] == '\0')
		return (EXIT_FAILURE);
	while (args && args[index]
	&& (ft_isalnum(args[index]) == 1 || args[index] == '_'))
		index++;
	if (args[index])
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		ft_is_redirection(char *token)
{
	if (ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0
	|| ft_strcmp(token, ">>") == 0)
		return (1);
	return (0);
}

int		ft_is_operator(char *token)
{
	if (ft_strcmp(token, ";") == 0)
		return (1);
	if (ft_strcmp(token, ";;") == 0)
		return (2);
	if (ft_strcmp(token, "&") == 0)
		return (3);
	if (ft_strcmp(token, "|") == 0 || ft_strcmp(token, "||") == 0
	|| ft_strcmp(token, "&&") == 0)
		return (4);
	if (ft_strcmp(token, "<") == 0 || ft_strcmp(token, "<<") == 0
	|| ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0)
		return (5);
	if (ft_strcmp(token, "\\") == 0)
		return (6);
	return (0);
}

int		ft_is_separator(char *str, int i)
{
	int escaped;

	escaped = ft_is_escaped(str, i);
	if (escaped == 0 && str[i] == ';')
		return (1);
	return (0);
}
