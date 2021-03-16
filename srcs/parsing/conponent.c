/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conponent.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:02:54 by jobenass          #+#    #+#             */
/*   Updated: 2021/03/12 11:31:31 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		ft_count_sequence(char **token)
{
	int		index;
	int		count;

	count = 0;
	index = -1;
	while (token[++index])
		if (ft_strcmp(token[index], "|") == 0)
			count++;
	return (count + 1);
}

int		**ft_set_pipes(int number)
{
	int		index;
	int		**mini_pipe;

	if (!(mini_pipe = malloc(sizeof(int *) * number)))
		return (NULL);
	ft_bzero(mini_pipe, sizeof(int *) * number);
	index = 0;
	while (mini_pipe && index < number)
	{
		if (!(mini_pipe[index] = malloc(sizeof(int) * 2)))
		{
			ft_tabnbrdel(&mini_pipe, index);
			return (NULL);
		}
		mini_pipe[index][IN] = -1;
		mini_pipe[index][OUT] = -1;
		index++;
	}
	return (mini_pipe);
}

int		ft_lenght_conponents(t_mini *shl, char **token, int i)
{
	int		size;

	size = 0;
	while (i + size < shl->lxr->length)
	{
		if (ft_strcmp(token[i + size], "|") == 0)
			break ;
		size++;
	}
	return (size);
}

int		ft_get_conponents(t_mini *shl, int size, int i)
{
	int		out;

	if (size == 0)
		return (EXIT_SUCCESS);
	if (!(shl->psr->arguments = malloc(sizeof(char *) * (size + 1))))
		return (EXIT_ERROR);
	out = 0;
	while (i < shl->lxr->length && ft_strcmp(shl->lxr->token[i], "|") != 0)
	{
		if (ft_edit_tilde(shl, &shl->lxr->token[i]) == EXIT_ERROR)
			return (EXIT_ERROR);
		if (i > 0 && ft_is_redirection(shl->lxr->token[i - 1]) == 1)
			shl->psr->arguments[out++] = ft_strdup(shl->lxr->token[i++]);
		else
		{
			shl->psr->arguments[out] = ft_strdup(shl->lxr->token[i++]);
			if (ft_edit_token(&shl->psr->arguments[out], \
			shl->env) == EXIT_ERROR)
				return (EXIT_ERROR);
			out++;
		}
	}
	shl->psr->arguments[out] = NULL;
	return (EXIT_SUCCESS);
}

void	ft_sort_conponents(char **arguments, int size)
{
	char	*tmp;
	int		index;

	if (size == 0)
		return ;
	index = 0;
	while (index < size)
	{
		if (arguments[index] == NULL && arguments[index + 1] != NULL)
		{
			tmp = arguments[index];
			arguments[index] = arguments[index + 1];
			arguments[index + 1] = tmp;
			index = -1;
		}
		index++;
	}
}
