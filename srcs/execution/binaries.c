/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninieddu <ninieddu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:50:24 by jobenass          #+#    #+#             */
/*   Updated: 2021/01/20 16:34:13 by ninieddu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int			ft_execute_binaries(t_mini *shl, int in, int out)
{
	// int		backup;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		// backup = dup(STDOUT_FILENO);
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		exit(execve(shl->psr->command, shl->psr->arguments, shl->env));
		// dup2(backup, out);
	}
	else if (pid > 0)
	{
		if (ft_strcmp(shl->psr->command, "/Users/ninieddu/Desktop/4_Minishell_Project/minishell") == 0) /////
			ft_signal_handler(2);
		else
			ft_signal_handler(0);
		if (out != STDOUT_FILENO)
			close(out);
		waitpid(pid, &status, 0);
  		if (WIFEXITED(status))
			return(WEXITSTATUS(status));
		if (WIFSIGNALED(status))
			return(WTERMSIG(status));
	}
	else
		return (ft_error("fork", NULL));
	return (ft_error(shl->lxr->token[0], NULL));
}
