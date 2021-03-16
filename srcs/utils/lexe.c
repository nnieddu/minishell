/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_last.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:21:15 by ninieddu          #+#    #+#             */
/*   Updated: 2021/03/10 11:39:09 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		ft_is_escaped(char *str, int i)
{
	int		escaped;

	escaped = 0;
	while (i > 0 && str[i - 1] == '\\')
	{
		if (escaped == 0)
			escaped = 1;
		else
			escaped = 0;
		i--;
	}
	return (escaped);
}

int		ft_is_quote(char *str, int i, int quote)
{
	int escaped;

	escaped = ft_is_escaped(str, i);
	if (escaped == 0 && quote == '\0'
	&& (str[i] == '\'' || str[i] == '\"'))
		quote = str[i];
	else if (escaped == 0 && quote == '\"' && quote == str[i])
		quote = '\0';
	else if (quote == '\'' && quote == str[i])
		quote = '\0';
	return (quote);
}

int		ft_is_token(char *str, int i)
{
	int escaped;

	escaped = ft_is_escaped(str, i);
	if (escaped == 1
	&& (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
		return (1);
	if ((str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
		return (1);
	return (0);
}

int		ft_is_metachar(char *str, int i)
{
	int escaped;

	escaped = ft_is_escaped(str, i);
	if (escaped == 0 &&
	((str[i] == '>' && str[i + 1] != '>')
	|| (str[i] == '<' && str[i + 1] != '<')))
		return (1);
	if (escaped == 0
	&& ((str[i] == '>' && str[i + 1] == '>')
	|| (str[i] == '<' && str[i + 1] == '<')))
		return (2);
	if (escaped == 0
	&& ((str[i] == '|' && str[i + 1] != '|')
	|| (str[i] == '&' && str[i + 1] != '&')))
		return (1);
	if (escaped == 0
	&& ((str[i] == '|' && str[i + 1] == '|')
	|| (str[i] == '&' && str[i + 1] == '&')))
		return (2);
	if (escaped == 0 && (str[i] == ';' && str[i + 1] != ';'))
		return (1);
	if (escaped == 0 && str[i] == ';' && str[i + 1] == ';')
		return (2);
	return (0);
}

int		ft_is_only_spaces(char *str)
{
	int		i;

	i = 0;
	while (str[i] && ft_isspace(str[i]) == 1)
		i++;
	if (!str[i])
		return (1);
	return (0);
}
