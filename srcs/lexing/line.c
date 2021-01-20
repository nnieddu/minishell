////////////////////////////////////////////////////////////////////////////////
//
// 		███    ██  ██████  ████████ ███████ ███████ 
// 		████   ██ ██    ██    ██    ██      ██      
// 		██ ██  ██ ██    ██    ██    █████   ███████ 
// 		██  ██ ██ ██    ██    ██    ██           ██ 
// 		██   ████  ██████     ██    ███████ ███████ 
//
//
////////////////////////////////////////////////////////////////////////////////

#include "../../incs/minishell.h"

static void	ft_write_line(char **line, char *input)
{
	int		quote;
	int		meta;
	int		in;
	int		out;

	quote = '\0';
	in = 0;
	out = 0;
	while (input && input[in])
	{
		quote = ft_is_quote(input, in, quote);
		if (quote == '\0'
		&& (meta = ft_is_metachar(input, in)) > 0)
		{
			if (out > 0 && (*line)[out - 1] != ' ')
				(*line)[out++] = ' ';
			while (meta--)
				(*line)[out++] = input[in++];
			if (input[in] && input[in] != ' ')
				(*line)[out++] = ' ';
		}
		else
			(*line)[out++] = input[in++];
	}
}

static int	ft_length_line(char *line)
{
	int		quote;
	int		meta;
	int		add;
	int		index;

	quote = '\0';
	add = 0;
	index = 0;
	while (line && line[index])
	{
		quote = ft_is_quote(line, index, quote);
		if (quote == '\0'
		&& (meta = ft_is_metachar(line, index)) > 0)
		{
			if (index > 0 && ft_is_token(line[index - 1]) == 1)
				add++;
			index += meta;
			if (line[index] && ft_is_token(line[index]) == 1
			&& ft_is_metachar(line, index) == 0)
				add++;
		}
		else
			index++;
	}
	return (index += add);
}

char		*ft_get_line(char *input)
{
	char	*line;
	int		length;

	if (!input)
		return (NULL);
	length = ft_length_line(input);
	if (!(line = ft_strnew(length)))
		return (NULL);
	ft_write_line(&line, input);
	return (line);
}