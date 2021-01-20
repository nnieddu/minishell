////////////////////////////////////////////////////////////////////////////////
//
// 		███    ██  ██████  ████████ ███████ ███████ 
// 		████   ██ ██    ██    ██    ██      ██      
// 		██ ██  ██ ██    ██    ██    █████   ███████ 
// 		██  ██ ██ ██    ██    ██    ██           ██ 
// 		██   ████  ██████     ██    ███████ ███████ 
//
//		ERREUR:
//		"echo | ||" --> | et non ||
//		"echo >   " --> near parse error et non être valide
//
////////////////////////////////////////////////////////////////////////////////

#include "../../incs/minishell.h"

static int	ft_is_control(char *input, int index)
{
	if ((index == 0 && input[index] == ';')
	|| (index > 0 && input[index - 1] != '\\' && input[index] == ';'))
		return (1);
	if ((index == 0 && input[index] == '|')
	|| (index > 0 && input[index - 1] != '\\' && input[index] == '|'))
		return (1);
	if ((index == 0 && input[index] == '&')
	|| (index > 0 && input[index - 1] != '\\' && input[index] == '&'))
		return (1);
	if ((index == 0 && input[index] == '<')
	|| (index > 0 && input[index - 1] != '\\' && input[index] == '<'))
		return (1);
	if ((index == 0 && input[index] == '>')
	|| (index > 0 && input[index - 1] != '\\' && input[index] == '>'))
		return (1);
	return (0);
}

static int	ft_before_control(char *input, int index, int token, int quote)
{
	int		error;

	error = 0;
	if (token == 0 && quote == '\0' && ft_is_control(input, index) == 1)
	{
		if (input[index] == '<' || input[index] == '>')
			ft_putstr("syntax error near unexpected token `newline");
		else
		{
			ft_putstr("syntax error near unexpected token `");
			ft_putchar(input[index]);
			if (input[index + 1] && ft_is_control(input, index + 1) == 1)
				ft_putchar(input[index + 1]);
		}
		ft_putstr("'\n");
		error = 1;
	}
	return(error);
}

static int	ft_after_control(char *input, int control, int quote)
{
	int		error;

	error = 0;
	if (quote == '\0' && control != 0)
	{
		if (input[control] == '<' || input[control] == '>')
			ft_putstr("syntax error near unexpected token `newline");
		else
		{
			ft_putstr("syntax error unauthorized multiline token `");
			ft_putchar(input[control]);
			if (control > 0 && ft_is_control(input, control - 1) == 1)
				ft_putchar(input[control - 1]);
		}
		ft_putstr("'\n");
		error = 1;
	}
	else if (quote == '\'')
		ft_putstr("syntax error unauthorized multiline token `\''\n");
	else if (quote == '\"')
		ft_putstr("syntax error unauthorized multiline token `\"'\n");
	if (quote == '\'' || quote == '\"')
		error = 1;
	return(error);
}

static int	ft_last_control(char *input, int index, int quote, int *token)
{
	if (quote == '\0' && ft_is_token(input[index]) == 1
	&& ft_is_control(input, index) == 1 && input[index] != ';')
		return (index);
	if (quote == '\0' && ft_is_token(input[index]) == 1
	&& ft_is_control(input, index) == 0)
	{
		*token = ft_is_token(input[index]);
		return(0);
	}
	if (quote == '\0' && ft_is_token(input[index]) == 0
	&& ft_is_control(input, index) == 1)
		return(index);
	return (0);
}

int		ft_check_syntax(char *input)
{
	int		quote;
	int		token;
	char	control;
	int		index;

	quote = '\0';
	token = 0;
	control = '\0';
	index = 0;
	while (input[index])
	{
		quote = ft_is_quote(input, index, quote);
		control = ft_last_control(input, index, quote, &token);
		if (token == 0 && ft_is_control(input, index) == 1)
			break ;
		if (quote == '\0' && input[index] == ';')
			token = 0;
		index++;
	}
	if (ft_before_control(input, index, token, quote) == 1
	|| ft_after_control(input, control, quote) == 1)
		return (EXIT_FAILURE);
	return(EXIT_SUCCESS);
}