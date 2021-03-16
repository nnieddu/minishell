/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninieddu <ninieddu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:06:35 by jobenass          #+#    #+#             */
/*   Updated: 2021/03/15 20:29:37 by ninieddu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	ft_clear_tokens(char **argument, char **input)
{
	if (*argument)
		ft_strdel(argument);
	if (*input)
		ft_strdel(input);
}

static int	ft_get_file(char **operand, char **input, int *fd, char **env)
{
	char	*save;
	int		*file;

	file = NULL;
	if (ft_strcmp(*operand, "<") == 0)
		file = &fd[IN];
	else if (ft_strcmp(*operand, ">") == 0 || ft_strcmp(*operand, ">>") == 0)
		file = &fd[OUT];
	if ((save = ft_strdup(*input)) == NULL)
		return (EXIT_ERROR);
	ft_edit_token(input, env);
	if (file != NULL && *input)
		*file = ft_browse_redirection(*operand, *input);
	if (*input == NULL)
	{
		*input = save;
		ft_error(save, NULL, "ambiguous redirect", 0);
		return (EXIT_FAILURE);
	}
	else
		ft_strdel(&save);
	ft_error(*input, NULL, NULL, 0);
	ft_clear_tokens(operand, input);
	return (*file != -1 ? EXIT_SUCCESS : EXIT_FAILURE);
}

static int	ft_get_pipe(int *mini_pipe)
{
	int		ret;

	ret = pipe(mini_pipe);
	return (ret != -1 ? EXIT_SUCCESS : EXIT_ERROR);
}

static int	ft_get_type(char **token, int i, int id)
{
	if (ft_is_redirection(token[i]) == 1 && token[i + 1])
		return (1);
	if (ft_strcmp(token[i], "|") == 0 && id != -1)
		return (2);
	return (0);
}

int			ft_get_redirection(t_mini *shl, int i, int id, int ret)
{
	int		type;
	int		j;

	shl->psr->fd[IN] = STDIN_FILENO;
	shl->psr->fd[OUT] = STDOUT_FILENO;
	j = 0;
	while (i < shl->lxr->length)
	{
		if ((type = ft_get_type(shl->lxr->token, i, id)) == FILE && ret == 0)
		{
			ret = ft_get_file(&shl->psr->arguments[j], \
			&shl->psr->arguments[j + 1], shl->psr->fd, shl->env);
			if (ret != EXIT_SUCCESS && ft_is_pipe(i, shl) == 0)
				return (ret);
		}
		else if (type == PIPE)
			if (ft_get_pipe(shl->psr->mini_pipe[id]) == EXIT_ERROR)
				return (EXIT_ERROR);
		if (type == PIPE)
			break ;
		i++;
		j++;
	}
	return (EXIT_SUCCESS);
}
