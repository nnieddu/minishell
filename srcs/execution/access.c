/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninieddu <ninieddu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:01:54 by jobenass          #+#    #+#             */
/*   Updated: 2021/03/10 12:55:48 by ninieddu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int				ft_command_exist(char *command)
{
	int			find;

	find = open(command, O_RDONLY, S_IRWXU);
	errno = 0;
	if (find < 0)
		return (EXIT_FAILURE);
	close(find);
	return (EXIT_SUCCESS);
}

static int		ft_access_directory(char *path)
{
	struct stat	info;
	int			access;
	DIR			*directory;

	directory = NULL;
	access = stat(path, &info);
	if (access == 0 && S_ISDIR(info.st_mode) == 1)
		if ((directory = opendir(path)) != NULL)
			closedir(directory);
	return (errno == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}

static int		ft_access_file(char *path)
{
	struct stat	info;
	int			access;
	int			fd;

	fd = -1;
	access = stat(path, &info);
	if (access == 0 && S_ISDIR(info.st_mode) == 1)
		fd = open(path, O_WRONLY, S_IRWXU);
	else if ((access == 0 && S_ISREG(info.st_mode) == 1))
		fd = open(path, O_RDONLY, S_IRWXU);
	if (fd != -1)
		close(fd);
	return (errno == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}

static char		*ft_add_parts(char *input, int *length, char **path)
{
	char		*tmp;

	if (input[*length] == '/')
		(*length)++;
	if (!*path && !(*path = ft_strdup("")))
		return (NULL);
	tmp = *path;
	*path = ft_strjoin_idx(tmp, input, *length);
	ft_strdel(&tmp);
	return (*path);
}

int				ft_browse_path(char *input)
{
	int			index;
	int			length;
	char		*path;
	int			ret;

	path = NULL;
	ret = EXIT_SUCCESS;
	index = 0;
	while (ret == EXIT_SUCCESS && input && input[index])
	{
		length = ft_strlen_chr(&input[index], '/');
		if ((path = ft_add_parts(&input[index], &length, &path)) == NULL)
			return (EXIT_ERROR);
		index += length;
		if (!input[index])
			break ;
		ret = ft_access_directory(path);
	}
	if (!input && (path = ft_strdup("")) == NULL)
		return (EXIT_ERROR);
	if (path && ret == EXIT_SUCCESS)
		ret = ft_access_file(path);
	ft_strdel(&path);
	return (ret);
}
