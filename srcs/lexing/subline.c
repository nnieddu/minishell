/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:02:29 by jobenass          #+#    #+#             */
/*   Updated: 2021/02/18 08:14:33 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	ft_append_list(char *subline, t_list **list)
{
	t_list	*item;

	if (!(item = ft_create_item(subline)))
		return (EXIT_ERROR);
	ft_add_item(list, item);
	return (EXIT_SUCCESS);
}

static int	ft_length_subline(char *line, int start)
{
	int		quote;
	int		length;

	quote = '\0';
	length = 0;
	while (line[start + length])
	{
		quote = ft_is_quote(line, start + length, quote);
		if (quote == '\0'
		&& ft_is_separator(line, start + length) == 1)
			break ;
		length++;
	}
	return (length);
}

static char	*ft_extract_subline(char *line, int lenght)
{
	char	*subline;

	subline = ft_strdup_idx(line, lenght);
	return (subline);
}

static int	ft_collect_subline(t_list **list, char *line)
{
	char	*subline;
	int		start;
	int		end;

	subline = NULL;
	start = 0;
	while (line[start])
	{
		end = ft_length_subline(line, start);
		if (!(subline = ft_extract_subline(&line[start], end)))
			return (EXIT_ERROR);
		if (ft_append_list(subline, list) == EXIT_ERROR)
		{
			ft_strdel(&subline);
			return (EXIT_ERROR);
		}
		ft_strdel(&subline);
		while (line[start + end] == ';')
			end++;
		start += end;
	}
	return (EXIT_SUCCESS);
}

char		**ft_get_subline(char *line)
{
	t_list	*list;
	char	**subline;
	int		error;

	if (!line)
		return (NULL);
	list = NULL;
	if ((error = ft_collect_subline(&list, line)) == EXIT_ERROR
	|| !(subline = ft_list_to_tab(list)))
	{
		ft_clean_list(&list);
		return (NULL);
	}
	ft_clean_list(&list);
	return (subline);
}
