/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninieddu <ninieddu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:03:17 by jobenass          #+#    #+#             */
/*   Updated: 2021/03/15 20:30:14 by ninieddu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	ft_next_step(t_mini *shl, int *id, int number, int *i)
{
	while (*i < shl->lxr->length)
	{
		if (ft_strcmp(shl->lxr->token[*i], "|") == 0)
		{
			(*i)++;
			break ;
		}
		(*i)++;
	}
	if (!shl->lxr->token[*i])
		*i = -1;
	if (*id >= 0 && *id < (number - 1))
		(*id)++;
	else
		*id = -1;
}

static void	ft_clean_arguments(char ***arguments, int size)
{
	int		i;

	if (!arguments || !*arguments)
		return ;
	i = 0;
	while (i < size)
	{
		if ((*arguments)[i])
		{
			free((*arguments)[i]);
			(*arguments)[i] = NULL;
		}
		i++;
	}
	free(*arguments);
	*arguments = NULL;
}

void		ft_clean_parser(t_parser **psr, int number, int size)
{
	if (!*psr)
		return ;
	ft_tabnbrdel(&(*psr)->mini_pipe, number);
	ft_clean_arguments(&(*psr)->arguments, size);
	free(*psr);
	*psr = 0;
}

static int	ft_prepare_parser(t_mini **shl, int *id, int *number, int *i)
{
	(*shl)->lxr->length = ft_tabstrlen((*shl)->lxr->token);
	g_pid = -1;
	if (!((*shl)->psr = malloc(sizeof(t_parser))))
		return (EXIT_ERROR);
	ft_bzero((*shl)->psr, sizeof(t_parser));
	*id = -1;
	if ((*number = ft_count_sequence((*shl)->lxr->token)) > 1
	&& !((*shl)->psr->mini_pipe = ft_set_pipes(*number - 1)))
		return (EXIT_ERROR);
	if ((*shl)->psr->mini_pipe)
		*id = 0;
	*i = 0;
	return (EXIT_SUCCESS);
}

int			ft_parser(t_mini *shl, int ret, int size)
{
	int		number;
	int		id;
	int		i;

	if ((ret = ft_prepare_parser(&shl, &id, &number, &i)) == EXIT_ERROR)
		ret = EXIT_ERROR;
	while (ret != EXIT_ERROR && i > -1 && i < shl->lxr->length)
	{
		size = ft_lenght_conponents(shl, shl->lxr->token, i);
		if (ft_get_conponents(shl, size, i) == EXIT_ERROR)
			break ;
		if ((ret = ft_get_redirection(shl, i, id, 0)) == EXIT_ERROR)
			break ;
		ft_sort_conponents(shl->psr->arguments, size);
		if (ret == EXIT_SUCCESS)
			if ((ret = ft_execute(shl, number, id, ret)) == EXIT_ERROR)
				break ;
		ft_next_step(shl, &id, number, &i);
		ft_clean_arguments(&shl->psr->arguments, size);
	}
	ret = ft_set_others_ret(ret, NULL, shl);
	if (ret == EXIT_SUCCESS)
		ret = ft_end_exec(shl, ret, number, shl->pid);
	ft_clean_parser(&shl->psr, number, size);
	return (ret);
}
