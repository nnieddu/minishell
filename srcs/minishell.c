/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninieddu <ninieddu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:59:44 by jobenass          #+#    #+#             */
/*   Updated: 2021/03/15 22:15:59 by ninieddu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

pid_t	g_pid = -1;

static int	ft_set_required(t_mini **shl, char **envp)
{
	if (!(*shl = malloc(sizeof(t_mini))))
		return (EXIT_ERROR);
	ft_bzero(*shl, sizeof(t_mini));
	if (ft_get_home(*shl) == EXIT_ERROR
	|| ft_set_variables(*shl, envp) == EXIT_ERROR
	|| ft_update_variables((*shl)->env) == EXIT_ERROR)
		return (EXIT_ERROR);
	(*shl)->subminishell = 0;
	return (EXIT_SUCCESS);
}

void		ft_general_clean(t_mini **shl)
{
	if (!*shl)
		return ;
	ft_strdel(&(*shl)->home);
	ft_tabstrdel(&(*shl)->env);
	free(*shl);
	*shl = NULL;
}

char		*ft_get_input(int fd, char *line)
{
	char	buff[2];
	char	*tmp;

	buff[1] = 0;
	while (1)
	{
		tmp = line;
		if (read(fd, buff, 1) == 0)
		{
			if (!tmp)
				break ;
			continue ;
		}
		if (!(line = ft_strjoin((line ? line : "\0"), \
			(*buff == '\n' ? "\0" : buff))))
			return (NULL);
		if (tmp)
			free(tmp);
		if (*buff == '\n')
			break ;
	}
	return (line);
}

void		ft_prompt(void)
{
	ft_putstr_fd("minishell-42", 1);
	ft_putstr_fd("$ ", 1);
}

int			main(int argc, char **argv, char **envp)
{
	t_mini	*shl;
	char	*input;
	int		ret;

	shl = NULL;
	input = NULL;
	ret = ft_set_required(&shl, envp);
	while (ret != EXIT_ERROR && argc && argv)
	{
		ft_signal_handler(1);
		ft_prompt();
		if (!(input = ft_get_input(0, NULL)))
			return (ft_manage_ctrld(input, &shl));
		ft_set_sign_ret(shl);
		ret = ft_lexer(shl, input, ret);
		ft_strdel(&input);
		if (ft_set_others_ret(ret, input, shl) == EXIT_ERROR)
			return (EXIT_ERROR);
		if (shl->exit == 1)
			break ;
	}
	ft_general_clean(&shl);
	if (ret == EXIT_ERROR)
		ft_fatal_error();
	return (ret);
}
