/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninieddu <ninieddu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:18:52 by ninieddu          #+#    #+#             */
/*   Updated: 2021/03/15 01:05:17 by ninieddu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		ft_is_empty(char *str)
{
	int		i;

	i = -1;
	while (str && str[++i])
		if (ft_is_escaped(str, i) == 0 && (str[i] == '\'' || str[i] == '\"'))
			return (1);
	return (0);
}

int		ft_is_quoted(char *str, int i, int *quote)
{
	int escaped;

	escaped = ft_is_escaped(str, i);
	if (escaped == 0 && *quote == '\0' && (str[i] == '\'' || str[i] == '\"'))
	{
		*quote = str[i];
		return (1);
	}
	else if (((escaped == 0 && *quote == '\"')
	|| *quote == '\'') && str[i] == *quote)
	{
		*quote = '\0';
		return (1);
	}
	return (0);
}

int		ft_is_backslashed(char *str, int i, int quote)
{
	int		variable;
	int		escaped;

	variable = 0;
	while (str && str[i + variable] && str[i + variable] == '\\')
		variable++;
	escaped = ft_is_escaped(str, i);
	if (quote == '\'')
		return (0);
	if (quote == '\0' || str[i + variable] == '$')
		if (escaped == 0 && str[i] == '\\')
			return (1);
	if (quote == '\"' && str[i + variable] != '$')
		if (escaped == 1 && str[i] == '\\')
			return (1);
	return (0);
}

int		ft_is_charset(char *str, int i)
{
	if ((str[i] >= 'a' && str[i] <= 'z')
	|| (str[i] >= 'A' && str[i] <= 'Z')
	|| (str[i] >= '0' && str[i] <= '9')
	|| str[i] == '_')
		return (1);
	if (str[i] == '?')
		return (1);
	return (0);
}

int		ft_is_variable(char *str, int i, int quote)
{
	int escaped;

	escaped = ft_is_escaped(str, i);
	if (escaped == 0 && quote == '\0'
	&& str[i] == '$' && str[i + 1]
	&& (str[i + 1] == '\'' || str[i + 1] == '\"')
	&& (ft_is_charset(str, i + 1) == 0))
		return (1);
	if (escaped == 0 && quote != '\''
	&& str[i] == '$' && str[i + 1] && (ft_is_charset(str, i + 1) == 1))
		return (1);
	return (0);
}
