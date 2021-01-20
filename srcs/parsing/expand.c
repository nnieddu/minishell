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

static int	ft_write_env(char **token, char *old, int *out, char **env)
{
	char	*key;
	char	*content;
	int		new_in;
	int		index;

	key = 0;
	new_in = 0;
	while (ft_is_charset(old, new_in) == 1)
		new_in++;
	if (!(key = ft_strdup_idx(old, new_in)))
		return (-1);
	content = ft_get_env(env, key);
	index = 0;
	while (content && content[index])
		(*token)[(*out)++] = content[index++];
	// (*token)[(*out)] = '\0';
	ft_strdel(&key);
	return (new_in);
}

static int	ft_write_new_token(char **token, char *old, char **env)
{
	int		quote;
	int		in;
	int		out;
	int		res;

	quote = '\0';
	in = 0;
	out = 0;
	while (old[in])
	{
		res = 0;
		quote = ft_is_quote(old, in, quote);
		if (quote != '\'' && ft_is_variable(old, in, quote) == 1)
		{
			if ((res = ft_write_env(token, &old[in + 1], &out, env)) == -1)
				return (-1);
			in += res + 1;
		}
		else
			(*token)[out++] = old[in++];
	}
	return (0);
}

static int	ft_size_token(char *token, int *index, int *length, char **env)
{
	char	*key;
	char	*content;
	int		tmp;

	(*index)++;
	tmp = *index;
	while (ft_is_charset(token, *index) == 1)
		(*index)++;
	if (!(key = ft_strdup_idx(token, (*index - tmp))))
		return (-1);
	content = ft_get_env(env, key);
	if (content)
		(*length) += ft_strlen(content);
	ft_strdel(&key);
	return (*index);
}

static int	ft_length_new_token(char *token, char **env)
{
	int		quote;
	int		length;
	int		index;
	int		res;

	quote = '\0';
	length = 0;
	index = 0;
	while (token && token[index])
	{
		res = 0;
		quote = ft_is_quote(token, index, quote);
		if (quote != '\'' && ft_is_variable(token, index, quote) == 1)
		{
			res = ft_size_token(&token[index], &index, &length, env);
			if (res == -1)
				return (-1);
			index += res + 1;
		}
		else
			index++;
	}
	return (index + length);
}

int			ft_edit_variable(t_mini *shl, char **token)
{
	char	*tmp;
	int		length;
	int		index;

	tmp = NULL;
	length = 0;
	index = 0;
	while (token && token[index])
	{
		if (ft_need_expand(token[index]) == 1)
		{
			if ((length = ft_length_new_token(token[index], shl->env)) < 0)
				return (EXIT_FAILURE);
			tmp = token[index];
			token[index] = ft_strnew(length);
			if (!token[index])
				return (EXIT_FAILURE);
			ft_write_new_token(&token[index], tmp, shl->env);
			ft_strdel(&tmp);
		}
		index++;
	}
	return (EXIT_SUCCESS);
}