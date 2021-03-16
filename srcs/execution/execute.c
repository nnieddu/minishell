/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 07:36:35 by jobenass          #+#    #+#             */
/*   Updated: 2021/03/15 00:17:30 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		ft_close(int in, int out, int ret)
{
	if (in != STDIN_FILENO)
		close(in);
	if (out != STDOUT_FILENO)
		close(out);
	return (ret);
}

int		ft_define_input(int *fd, int **pipe, int number, int id)
{
	if (pipe)
	{
		if (fd[IN] != STDIN_FILENO)
		{
			if (id > 0 && id <= (number - 1))
				close(pipe[id - 1][IN]);
			return (fd[IN]);
		}
		else if (id > 0 && id <= (number - 1))
			return (pipe[id - 1][IN]);
	}
	else if (fd[IN] != STDIN_FILENO)
		return (fd[IN]);
	return (STDIN_FILENO);
}

int		ft_define_output(int *fd, int **pipe, int number, int id)
{
	if (pipe)
	{
		if (fd[OUT] != STDOUT_FILENO)
		{
			if (id >= 0 && id < (number - 1))
				close(pipe[id][OUT]);
			return (fd[OUT]);
		}
		else if (id >= 0 && id < (number - 1))
			return (pipe[id][OUT]);
	}
	else if (fd[OUT] != STDOUT_FILENO)
		return (fd[OUT]);
	return (STDOUT_FILENO);
}

int		ft_execute(t_mini *shl, int number, int id, int ret)
{
	int		in;
	int		out;

	in = ft_define_input(shl->psr->fd, shl->psr->mini_pipe, number, id);
	out = ft_define_output(shl->psr->fd, shl->psr->mini_pipe, number, id);
	if (shl->psr->arguments && !shl->psr->arguments[0])
		return (ft_close(in, out, 0));
	if (ft_manage_underscore(shl->env, shl->psr->arguments) == EXIT_ERROR)
		return (ft_close(in, out, -1));
	if ((ret = ft_get_command(shl, shl->env, shl->psr->arguments, 0)) \
	== EXIT_SUCCESS)
	{
		if (ft_is_builtins(shl->psr->arguments[0]) == 1)
			ret = ft_execute_builtins(shl, out);
		else
			ret = ft_execute_binaries(shl, in, out, id);
	}
	else
		ret = ft_close(in, out, ret);
	ft_strdel(&shl->psr->command);
	return (ret);
}
