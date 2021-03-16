/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninieddu <ninieddu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:03:25 by jobenass          #+#    #+#             */
/*   Updated: 2021/03/15 21:46:48 by ninieddu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_doublestrdel(char **str1, char **str2)
{
	if (*str1)
		ft_strdel(str1);
	if (*str2)
		ft_strdel(str2);
}

char	*ft_get_env(char **env, char *key)
{
	char	*var;
	int		i;

	if (!env)
		return (NULL);
	var = ft_strjoin(key, "=");
	i = -1;
	while (env[++i] && var)
		if (ft_strcmp_chr(env[i], var, '=') == 0)
			break ;
	ft_strdel(&var);
	if (env[i])
		return (ft_strchr(env[i], '=') + 1);
	return (NULL);
}

char	**ft_list_to_tab(t_list *list)
{
	char	**token;
	int		len;
	int		i;

	token = NULL;
	len = ft_list_size(list);
	if (!(token = malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	i = -1;
	while (++i < len)
	{
		if (!(token[i] = ft_strdup(list->content)))
		{
			ft_tabstrdel(&token);
			return (NULL);
		}
		list = list->next;
	}
	token[i] = NULL;
	return (token);
}

char	*ft_join_path(char *dir, char *command)
{
	char	*binary;
	char	*path;

	if (dir[ft_strlen(dir) - 1] != '/')
		path = ft_strjoin(dir, "/");
	else
		path = ft_strdup(dir);
	if (!path)
		return (NULL);
	binary = ft_strjoin(path, command);
	ft_strdel(&path);
	return (binary);
}
