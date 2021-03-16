/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninieddu <ninieddu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:02:34 by jobenass          #+#    #+#             */
/*   Updated: 2021/03/15 01:07:11 by ninieddu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	ft_error_multiline(char *token, int quote)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error unauthorized multiline token `", STDERR_FILENO);
	if (token)
		ft_putstr_fd(token, STDERR_FILENO);
	else
		ft_putchar_fd(quote, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

static int	ft_error_token(char *token)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	if (token)
		ft_putstr_fd(token, STDERR_FILENO);
	else
		ft_putstr_fd("newline", STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

static int	ft_handle_error(char **token, int idx)
{
	if (ft_is_operator(token[idx]) == 1
	&& (idx == 0 || (idx > 0 && ft_is_operator(token[idx - 1]) != 0)))
		return (ft_error_token(token[idx]));
	if (idx > 0 && ft_is_operator(token[idx]) == 1 && token[idx + 1]
	&& ft_is_operator(token[idx + 1]) != 0 \
		&& ft_is_operator(token[idx + 1]) != 5)
		return (ft_error_token(token[idx + 1]));
	if (ft_is_operator(token[idx]) == 2)
		return (ft_error_token(token[idx]));
	if (ft_is_operator(token[idx]) == 3)
		return (ft_error_token(token[idx]));
	if (idx > 0 && ft_is_operator(token[idx]) == 4 && token[idx + 1] == NULL)
		return (ft_error_multiline(token[idx], '\0'));
	if (ft_is_operator(token[idx]) == 4
	&& (idx == 0 || (idx > 0 && ft_is_operator(token[idx - 1]) != 0)))
		return (ft_error_token(token[idx]));
	if (ft_is_operator(token[idx]) == 5 && token[idx + 1] == NULL)
		return (ft_error_token(NULL));
	if (ft_is_operator(token[idx]) == 5 && ft_is_operator(token[idx + 1]) != 0)
		return (ft_error_token(token[idx + 1]));
	if (ft_is_operator(token[idx]) == 6)
		return (ft_error_token(token[idx]));
	return (EXIT_SUCCESS);
}

int			ft_check_tokens(t_mini *shl, char **line)
{
	char	**token;
	int		index;
	int		ret;

	if ((token = ft_get_token(*line)) == NULL)
		return (EXIT_ERROR);
	ret = EXIT_SUCCESS;
	index = 0;
	while (ret == EXIT_SUCCESS && token && token[index])
	{
		ret = ft_handle_error(token, index);
		index++;
	}
	ft_tabstrdel(&token);
	if (ret != EXIT_SUCCESS)
	{
		ft_strdel(line);
		ft_clean_lexer(&shl->lxr);
	}
	return (ret == EXIT_SUCCESS ? EXIT_SUCCESS : EXIT_FAILURE);
}

int			ft_check_quotes(char *input)
{
	int		quote;
	int		index;

	quote = '\0';
	index = -1;
	while (input[++index])
		quote = ft_is_quote(input, index, quote);
	return (quote == '\0' ? EXIT_SUCCESS : ft_error_multiline(NULL, quote));
}
