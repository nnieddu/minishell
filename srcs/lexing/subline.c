////////////////////////////////////////////////////////////////////////////////
//
// 		███    ██  ██████  ████████ ███████ ███████ 
// 		████   ██ ██    ██    ██    ██      ██      
// 		██ ██  ██ ██    ██    ██    █████   ███████ 
// 		██  ██ ██ ██    ██    ██    ██           ██ 
// 		██   ████  ██████     ██    ███████ ███████ 
//
////////////////////////////////////////////////////////////////////////////////

#include "../../incs/minishell.h"

static int	ft_append_list(char *subline, t_list **list)
{
	t_list	*item;

	item = ft_create_item(subline);
	if (!item)
		return (EXIT_FAILURE);
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

	subline = 0;
	start = 0;
	while (line[start])
	{
		end = ft_length_subline(line, start);
		if (!(subline = ft_extract_subline(&line[start], end)))
			return (EXIT_FAILURE);
		if (ft_append_list(subline, list) == EXIT_FAILURE)
		{
			ft_strdel(&subline);
			return (EXIT_FAILURE);
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
	list = 0;
	error = ft_collect_subline(&list, line);
	if (error == EXIT_FAILURE)
	{
		ft_clean_list(&list);
		return (NULL);
	}
	subline = ft_list_to_tab(list);
	ft_clean_list(&list);
	return (subline);
}