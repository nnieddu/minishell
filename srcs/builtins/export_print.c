/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:01:19 by jobenass          #+#    #+#             */
/*   Updated: 2021/03/09 09:53:53 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	ft_print_key(const char *s, int fd)
{
	int		i;

	i = 0;
	while (s && s[i])
	{
		write(fd, &s[i], 1);
		if (s[i] == '=')
			break ;
		i++;
	}
}

static void	ft_print_env(char **copy, int out)
{
	char	*ptr;
	int		i;

	i = -1;
	while (copy[++i])
	{
		if (ft_strcmp_chr(copy[i], "?=", '=') != 0
		&& ft_strcmp_chr(copy[i], "_=", '=') != 0)
		{
			ft_putstr_fd("declare -x ", out);
			ft_print_key(copy[i], out);
			ptr = ft_strchr(copy[i], '=');
			if (ptr)
				ft_putchar_fd('"', out);
			if (ptr && (ptr + 1))
				ft_putstr_fd((ptr + 1), out);
			if (ptr)
				ft_putchar_fd('"', out);
			ft_putchar_fd('\n', out);
		}
	}
}

static void	ft_sort_env(char **copy)
{
	char	*tmp;
	int		len;
	int		i;

	i = 0;
	while (copy[i])
	{
		len = ft_strlen_chr(copy[i], '=');
		if (copy[i + 1] && ft_strncmp(copy[i], copy[i + 1], len) > 0)
		{
			tmp = copy[i];
			copy[i] = copy[i + 1];
			copy[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
}

static char	**ft_copy_env(char **old)
{
	char	**new;
	int		i;

	if (!(new = malloc(sizeof(char *) * (ft_tabstrlen(old) + 1))))
		return (NULL);
	ft_bzero(new, ft_tabstrlen(old) + 1);
	i = -1;
	while (old && old[++i])
	{
		if (!(new[i] = ft_strdup(old[i])))
		{
			ft_tabstrdel(&new);
			return (NULL);
		}
	}
	new[i] = NULL;
	return (new);
}

int			ft_print_environment(char **envs, int out)
{
	char	**copy;

	if ((copy = ft_copy_env(envs)) == NULL)
		return (EXIT_ERROR);
	ft_sort_env(copy);
	ft_print_env(copy, out);
	ft_tabstrdel(&copy);
	return (EXIT_SUCCESS);
}
