/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninieddu <ninieddu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:23:48 by ninieddu          #+#    #+#             */
/*   Updated: 2021/01/20 16:40:42 by ninieddu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_sigint(int sign)
{
	(void)sign;
	write(1, "\n", 1);
	ft_prompt();
}

void	ft_sigquit(int sign)
{
	(void)sign;
	ft_putstr_fd("\b\b  \b\b", 1);
}

void	ft_sigint_child(int sign)
{
	write(1, "\n", 1);
	kill(pid, sign);
}

void	ft_sigquit_child(int sign)
{
	ft_putstr_fd("Quitter (core dumped)\n", 1);
	kill(pid, sign);
}

void	ft_signal_handler(int flag)
{
	if (flag == 2)
	{
		signal(SIGINT, ft_sign_mini);
		signal(SIGQUIT, ft_sign_mini);
	}

	if (flag == 1)
	{
		signal(SIGINT, ft_sigint);
		signal(SIGQUIT, ft_sigquit);
	}
	if (flag == 0)
	{
		signal(SIGINT, ft_sigint_child);
		signal(SIGQUIT, ft_sigquit_child);
	}
}