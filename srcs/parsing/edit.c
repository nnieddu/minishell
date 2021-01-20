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

static int	ft_is_escaped(char *str, int i, int quote)
{
	if (quote == '\0' && str[i] == '\\')
		return (1);
	if (quote == '\"' && str[i] == '\\'
	&& str[i + 1] && str[i + 1] == '\\')
		return (1);
	if (quote == '\"' && str[i] == '\\'
	&& str[i + 1] && str[i + 1] == '\"')
		return (1);
	return (0);
}

static int	ft_delete_quote(char *str, int i, int quote)
{
	if (i == 0 && quote != '\0')
		return (1);
	else if (i > 0 && quote == '\0' 
	&& str[i - 1] != '\\' && (str[i] == '\'' || str[i] == '\"'))
		return (1);
	if (i > 0 && quote != '\0'
	&& str[i - 1] != '\\' && str[i] == quote)
		return (1);
	return (0);
}

static void ft_write_new_token(char **token, char *old)
{
	int		quote;
	int		in;
	int		out;

	quote = '\0';
	in = 0;
	out = 0;
	while (old && old[in])
	{
		quote = ft_is_quote(old, in, quote);
		in += ft_delete_quote(old, in, quote);
		in += ft_is_escaped(old, in, quote);
		(*token)[out++] = old[in++];
	}
	(*token)[out] = old[in];
}

static int	ft_length_new_token(char *token)
{
	int		quote;
	int		length;
	int		index;

	quote = '\0';
	length = 0;
	index = 0;
	while (token && token[index])
	{
		quote = ft_is_quote(token, index, quote);
		length += ft_delete_quote(token, index, quote);
		length += ft_is_escaped(token, index, quote);
		index++;
	}
	index -= length;
	if (index <= 0)
		index = 0;
	return (index);
}

int			ft_edit_token(char **token)
{
	char	*tmp;
	int		length;
	int		index;

	length = 0;
	index = -1;
	while (token && token[++index])
	{
		length = ft_length_new_token(token[index]);
		tmp = token[index];
		token[index] = ft_strnew(length);
		if (!token[index])
			return (EXIT_FAILURE);
		if (length > 0)
			ft_write_new_token(&token[index], tmp);
		ft_strdel(&tmp);
	}
	return (EXIT_SUCCESS);
}
