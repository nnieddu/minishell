/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninieddu <ninieddu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:50:24 by jobenass          #+#    #+#             */
/*   Updated: 2021/03/15 21:12:51 by ninieddu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		ft_check_son_return(int status, int ret)
{
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 255)
			return (127);
		return (WEXITSTATUS(status));
	}
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (ret);
}

int		ft_end_exec(t_mini *shl, int ret, int pipe_count, pid_t master_pid)
{
	int		status;
	int		last_status;
	int		pid;

	last_status = 0;
	status = 0;
	while (pipe_count > 0)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1 && errno == ECHILD)
		{
			errno = 0;
			break ;
		}
		else if (pid == -1)
			return (EXIT_ERROR);
		pipe_count--;
		if (pid == master_pid)
			last_status = status;
		ret = ft_check_son_return(last_status, ret);
	}
	if (ft_manage_code(shl->env, ret) == EXIT_ERROR)
		ret = EXIT_ERROR;
	return (ret);
}

int		ft_son_exec(t_mini *shl, int in, int out, int id)
{
	if (dup2(in, STDIN_FILENO) == -1 || dup2(out, STDOUT_FILENO) == -1)
	{
		close(shl->psr->mini_pipe[id][IN]);
		close(shl->psr->mini_pipe[id][OUT]);
		exit(0);
	}
	if (in != -1)
		dup2(out, STDOUT_FILENO);
	execve(shl->psr->command, shl->psr->arguments, shl->env);
	if (errno == 13 || errno == 8)
		ft_error(shl->psr->arguments[0], NULL, "command not found", 0);
	exit(EXIT_ERROR);
}

int		ft_execute_binaries(t_mini *shl, int in, int out, int id)
{
	shl->pid = fork();
	if (shl->pid == 0)
		ft_son_exec(shl, in, out, id);
	else
	{
		if (g_pid == -1)
			g_pid = shl->pid;
		if (shl->subminishell == 0)
			ft_signal_handler(0);
		else
			ft_signal_handler(2);
		if (in != STDIN_FILENO && in != -1)
			close(in);
		if (out != STDOUT_FILENO && out != -1)
			close(out);
		return (EXIT_SUCCESS);
	}
	return (EXIT_ERROR);
}
