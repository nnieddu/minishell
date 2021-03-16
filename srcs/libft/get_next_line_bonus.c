/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 16:50:03 by jobenass          #+#    #+#             */
/*   Updated: 2020/06/26 12:55:07 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*ft_check_list(t_list **elem, int fd)
{
	t_list			*tmp;
	t_list			*new_elem;
	t_list			*last_elem;

	tmp = 0;
	if (*elem)
		tmp = *elem;
	while (tmp->next && tmp->id != fd)
		tmp = tmp->next;
	if (tmp && tmp->id != fd)
	{
		last_elem = tmp;
		if (!(new_elem = malloc(sizeof(t_list))))
			return (NULL);
		new_elem->id = fd;
		new_elem->rest = NULL;
		new_elem->next = NULL;
		last_elem->next = new_elem;
		return (new_elem);
	}
	return (tmp);
}

void	ft_delete_fd(t_list **elem, int fd)
{
	t_list			*tmp;
	t_list			*prev_elem;
	t_list			*next_elem;

	tmp = *elem;
	prev_elem = 0;
	next_elem = 0;
	while (tmp && tmp->id != fd)
	{
		if (tmp->next)
			prev_elem = tmp;
		tmp = tmp->next;
	}
	if (tmp->next)
		next_elem = tmp->next;
	if (!prev_elem)
		*elem = next_elem;
	else
		prev_elem->next = next_elem;
	free(tmp);
	tmp = 0;
}

int		ft_check_params(int fd, char **line, t_list **elem)
{
	if (fd < 0 || (read(fd, 0, 0) < 0) || !line)
		return (-1);
	if (BUFFER_SIZE <= 0)
	{
		*line = 0;
		return (-1);
	}
	if (!(*elem))
	{
		if (!(*elem = malloc(sizeof(t_list))))
			return (-1);
		(*elem)->id = fd;
		(*elem)->rest = 0;
		(*elem)->next = 0;
	}
	*line = 0;
	if (!(*line = malloc(sizeof(char) * 1)))
	{
		ft_free_reset_return(&(*elem)->rest, -1);
		ft_delete_fd(elem, fd);
		return (-1);
	}
	if (*line)
		*line[0] = '\0';
	return (0);
}

int		ft_process(char **line, t_list **elem, char **buff, int option)
{
	char	*tmp1;
	char	*tmp2;

	if (option == 1)
		tmp1 = (*elem)->rest;
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
		if ((*elem)->rest[0]
		&& !((*elem)->rest = ft_strdup_chr(ft_strchr(tmp1, '\n') + 1, '\0')))
		{
			ft_free_reset_return(&tmp1, -1);
			return (ft_free_reset_return(line, -1));
		}
		return (ft_free_reset_return(&tmp1, 1));
	}
	return (ft_free_reset_return(&(*elem)->rest, 0));
}

int		get_next_line_fd(int fd, char **line)
{
	char			*buff;
	int				pad;
	static t_list	*elem;
	t_list			*tmp;

	if ((pad = ft_check_params(fd, line, &elem)) && pad == -1)
		return (-1);
	if (!(tmp = ft_check_list(&elem, fd)))
		return (-1);
	if (tmp->rest && ((pad = ft_process(line, &tmp, 0, 1))) && pad == -1)
		ft_delete_fd(&elem, fd);
	if (pad != 0)
		return (pad);
	if (!(buff = malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (ft_free_reset_return(line, -1));
	while ((pad = read(fd, buff, BUFFER_SIZE)))
	{
		buff[pad] = '\0';
		if ((pad = ft_process(line, &tmp, &buff, 0)) && pad == -1)
			ft_delete_fd(&elem, fd);
		if (pad != 0)
			return (pad);
	}
	ft_delete_fd(&elem, fd);
	return (ft_free_reset_return(&buff, 0));
}
