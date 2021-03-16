/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 16:50:03 by jobenass          #+#    #+#             */
/*   Updated: 2021/02/18 08:15:26 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		ft_free_reset_return(char **str, int value)
{
	if (*str)
		free(*str);
	*str = 0;
	return (value);
}

static int		ft_check_params(int fd, char **line, char **rest)
{
	if (fd < 0 || (read(fd, 0, 0) < 0) || !line)
		return (-1);
	if (BUFFER_SIZE <= 0)
	{
		*line = 0;
		return (-1);
	}
	if (*line)
		*line = 0;
	if (!(*line = malloc(sizeof(char) * 1)))
		return (ft_free_reset_return(rest, -1));
	if (*line)
		*line[0] = '\0';
	return (0);
}

static int		ft_process(char **line, char **rest, char **buff, int option)
{
	char	*tmp1;
	char	*tmp2;

	if (option == 1)
		tmp1 = *rest;
	else
		tmp1 = *buff;
	tmp2 = *line;
	if (!(*line = ft_strjoin_chr(tmp2, '\0', tmp1, '\n')))
	{
		ft_free_reset_return(&tmp1, -1);
		return (ft_free_reset_return(&tmp2, -1));
	}
	ft_free_reset_return(&tmp2, -1);
	if (ft_strchr(tmp1, '\n'))
	{
		if (rest[0]
		&& !(*rest = ft_strdup_chr(ft_strchr(tmp1, '\n') + 1, '\0')))
		{
			ft_free_reset_return(&tmp1, -1);
			return (ft_free_reset_return(line, -1));
		}
		return (ft_free_reset_return(&tmp1, 1));
	}
	return (ft_free_reset_return(rest, 0));
}

int				get_next_line(int fd, char **line)
{
	char			*buff;
	int				pad;
	static char		*rest;

	if (ft_check_params(fd, line, &rest) == -1)
		return (-1);
	if (rest && ((pad = ft_process(line, &rest, 0, 1))) && pad != 0)
		return (pad);
	if (!(buff = malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (ft_free_reset_return(line, -1));
	while ((pad = read(fd, buff, BUFFER_SIZE)))
	{
		buff[pad] = '\0';
		if ((pad = ft_process(line, &rest, &buff, 0)) && pad != 0)
			return (pad);
	}
	return (ft_free_reset_return(&buff, 0));
}
