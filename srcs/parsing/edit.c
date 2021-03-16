/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:03:02 by jobenass          #+#    #+#             */
/*   Updated: 2021/03/14 11:23:15 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	ft_write_expand(char **token, char *old, int *out, char **env)
{
	char	*key;
	char	*content;
	int		index;
	int		in;

	index = 0;
	while (old && old[index] && ft_is_charset(old, index) == 1
	&& old[0] != '?')
		index++;
	if (index == 0 && old[0] == '?')
		index = 1;
	if (!(key = ft_strdup_idx(old, index)))
		return (EXIT_ERROR);
	content = ft_get_env(env, key);
	ft_strdel(&key);
	in = 0;
	while (content && content[in])
	{
		if (ft_is_backslashed(content, in, '\0') == 0)
			(*token)[(*out)++] = content[in];
		in++;
	}
	return (index);
}

static int	ft_length_expand(char *token, int *length, char **env)
{
	char	*key;
	char	*content;
	int		index;
	int		in;

	index = 0;
	while (token && token[index] && ft_is_charset(token, index) == 1
	&& token[0] != '?')
		index++;
	if (index == 0 && token[0] == '?')
		index = 1;
	if (!(key = ft_strdup_idx(token, index)))
		return (EXIT_ERROR);
	content = ft_get_env(env, key);
	ft_strdel(&key);
	in = 0;
	while (content && content[in])
	{
		if (ft_is_backslashed(content, in, '\0') == 0)
			(*length)++;
		in++;
	}
	return (index);
}

static int	ft_write_edit(char **token, char *old, char **env)
{
	int			quote;
	int			in;
	int			out;

	quote = '\0';
	in = 0;
	out = 0;
	while (old && old[in] && errno == 0)
	{
		if (ft_is_quoted(old, in, &quote) == 0
		&& ft_is_backslashed(old, in, quote) == 0)
		{
			if (ft_is_variable(old, in, quote) == 1)
				in += ft_write_expand(token, &old[in + 1], &out, env);
			else
				(*token)[out++] = old[in];
		}
		in++;
	}
	if (errno != 0)
		return (EXIT_ERROR);
	(*token)[out] = '\0';
	return (EXIT_SUCCESS);
}

static int	ft_length_edit(char *token, char **env)
{
	int		length;
	int		quote;
	int		index;

	length = ft_is_empty(token);
	quote = '\0';
	index = 0;
	while (token && token[index] && errno == 0)
	{
		if (ft_is_quoted(token, index, &quote) == 0
		&& ft_is_backslashed(token, index, quote) == 0)
		{
			if (ft_is_variable(token, index, quote) == 1)
				index += ft_length_expand(&token[index + 1], &length, env);
			else
				length++;
		}
		index++;
	}
	if (errno != 0)
		return (-1);
	return (length);
}

int			ft_edit_token(char **token, char **env)
{
	char	*tmp;
	int		length;

	if ((length = ft_length_edit(*token, env)) == -1)
		return (EXIT_ERROR);
	tmp = *token;
	if ((*token = ft_strnew(length)) == NULL)
	{
		*token = tmp;
		return (EXIT_ERROR);
	}
	if ((ft_write_edit(token, tmp, env)) == EXIT_ERROR)
	{
		ft_strdel(&tmp);
		return (EXIT_ERROR);
	}
	ft_strdel(&tmp);
	if (length == 0)
		ft_strdel(token);
	return (EXIT_SUCCESS);
}
