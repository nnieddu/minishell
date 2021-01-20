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

static int	ft_append_list(char *token, t_list **list)
{
	t_list	*item;

	item = ft_create_item(token);
	if (!item)
		return (EXIT_FAILURE);
	ft_add_item(list, item);
	return (EXIT_SUCCESS);
}

static int	ft_length_token(char *subline, int start)
{
	int		type;
	int		length;
	int		quote;

	type = subline[start];
	quote = '\0';
	length = 0;
	while (subline[start + length])
	{
		quote = ft_is_quote(subline, start + length, quote);
		if ((type == ' ' || type == '\t' || type == '\n')
		&& ft_is_token(subline[start + length]) == 1)
			break ;
		else if ((type != ' ' && type != '\t' && type != '\n') && quote == '\0'
		&& ft_is_token(subline[start + length]) == 0)
			break ;
		length++;
	}
	return (length);
}

static char	*ft_extract_token(char *subline, int lenght)
{
	char	*token;

	token = ft_strdup_idx(subline, lenght);
	if (token && ft_is_only_spaces(token) == 1)
	{
		ft_strdel(&token);
		if (!(token = ft_strnew(1)))
			return (NULL);
		token[0] = '\0';
	}
	return (token);
}

static int	ft_collect_token(t_list **list, char *subline)
{
	char	*token;
	int		start;
	int		end;

	token = 0;
	start = 0;
	while (subline[start])
	{
		end = ft_length_token(subline, start);
		if (!(token = ft_extract_token(&subline[start], end)))
			return (EXIT_FAILURE);
		if (token[0] != '\0' && ft_append_list(token, list) == EXIT_FAILURE)
		{
			ft_strdel(&token);
			return (EXIT_FAILURE);
		}
		ft_strdel(&token);
		start += end;
	}
	return (EXIT_SUCCESS);
}

char		**ft_get_token(char *subline)
{
	t_list	*list;
	char	**token;
	int		error;

	if (!subline)
		return (NULL);
	list = 0;
	error = ft_collect_token(&list, subline);
	if (error == EXIT_FAILURE)
	{
		ft_clean_list(&list);
		return (NULL);
	}
	token = ft_list_to_tab(list);
	ft_clean_list(&list);
	return (token);
}