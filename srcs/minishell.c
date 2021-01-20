/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninieddu <ninieddu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:59:44 by jobenass          #+#    #+#             */
/*   Updated: 2021/01/20 15:45:04 by ninieddu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static int	ft_set_required(t_mini **shl, char **envp)
{
	int		i;

	if (!(*shl = malloc(sizeof(t_mini))))
		return (EXIT_FAILURE);
	ft_bzero(*shl, sizeof(t_mini));
	if (!((*shl)->env = malloc(sizeof(char *) * (ft_tabstrlen(envp) + 2))))
		return (EXIT_FAILURE);
	i = -1;
	while (envp && envp[++i])
	{
		if (ft_strcmp_chr(envp[i], "SHLVL=", '=') == 0)
			(*shl)->env[i] = ft_manage_shlvl(envp[i]);
		else
			(*shl)->env[i] = ft_strdup(envp[i]);
		if (!(*shl)->env[i])
			return (EXIT_FAILURE);
	}
	if (ft_is_first_time(**&shl) == 1)
	{
		(*shl)->env[i] = ft_strjoin("?=", "0");
		if (!(*shl)->env[i])
			return (EXIT_FAILURE);
	}
	(*shl)->env[++i] = NULL;
	return (EXIT_SUCCESS);
}

void		ft_clean_general(t_mini **shl)
{
	if (!*shl)
		return ;
	ft_tabstrdel(&(*shl)->env);
	free(*shl);
	*shl = NULL;
}

char	*ft_get_input(int fd, char *line)
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
		if (!(line = ft_strjoin((line ? line : ""), \
			(*buff == '\n' ? "" : buff))))
		{
			ft_error("malloc", NULL);
			*buff = '\n';
		}
		if (tmp)
			free(tmp);
		if (*buff == '\n')
			break ;
	}
	return (line);
}

void		ft_prompt(void)
{
	char	*path;

	path = NULL;
	if ((path = getcwd(NULL, 0)))
	{
		ft_putstr_fd("minishell-42:~ ", 1);
		ft_putstr_fd(path, 1);
		ft_putstr_fd("$ ", 1);
		free(path);
	}
}

int			main(int argc, char**argv, char **envp)
{
	t_mini	*shl;
	char	*input;
	int		ret;

	shl = NULL;
	input = NULL;
	ret = ft_set_required(&shl, envp);
	while (argc && argv && (ret != EXIT_FAILURE))
	{
		ft_signal_handler(1);
		ft_prompt();
		if (!(input = ft_get_input(0, NULL)))
		{
			ft_putendl_fd("exit", 1);
			ft_strdel(&input);
			ft_clean_general(&shl);
			return (EXIT_SUCCESS);
		}
		ret = ft_lexer(shl, input, ret);
		if (shl->exit == 1)
			break ;
	}
	ft_clean_general(&shl);
	return (ret);
}