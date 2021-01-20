
#include "../../incs/minishell.h"

int			ft_is_quote(char *str, int i, int quote)
{
	if (i == 0 && quote == '\0'
	&& (str[i] == '\'' || str[i] == '\"'))
		quote = str[i];
	else if (i > 0 && quote == '\0'
	&& str[i - 1] != '\\' && (str[i] == '\'' || str[i] == '\"'))
		quote = str[i];
	else if (i > 0 && quote != '\0' && quote == str[i]
	&& str[i - 1] != '\\' && (str[i] == '\'' || str[i] == '\"'))
		quote = '\0';
	return (quote);
}

static int	ft_is_metachar_suit(char *str, int i)
{
	if (i > 0 && str[i - 1] != '\\'
	&& ((str[i] == '>' && str[i + 1] != '>')
	|| (str[i] == '<' && str[i + 1] != '<')))
		return (1);
	if (i > 0 && str[i - 1] != '\\'
	&& ((str[i] == '>' && str[i + 1] == '>')
	|| (str[i] == '<' && str[i + 1] == '<')))
		return (2);
	if (i > 0 && str[i - 1] != '\\'
	&& ((str[i] == '|' && str[i + 1] != '|')
	|| (str[i] == '&' && str[i + 1] != '&')))
		return (1);
	if (i > 0 && str[i - 1] != '\\'
	&& ((str[i] == '|' && str[i + 1] == '|')
	|| (str[i] == '&' && str[i + 1] == '&')))
		return (2);
	return (0);
}

int			ft_is_metachar(char *str, int i)
{
	if (i == 0
	&& ((str[i] == '>' && str[i + 1] != '>')
	|| (str[i] == '<' && str[i + 1] != '<')))
		return (1);
	if (i == 0
	&& ((str[i] == '>' && str[i + 1] == '>')
	|| (str[i] == '<' && str[i + 1] == '<')))
		return (2);
	if (i == 0
	&& ((str[i] == '|' && str[i + 1] != '|')
	|| (str[i] == '&' && str[i + 1] != '&')))
		return (1);
	if (i == 0
	&& ((str[i] == '|' && str[i + 1] == '|')
	|| (str[i] == '&' && str[i + 1] == '&')))
		return (2);
	return (ft_is_metachar_suit(str, i));
}

int			ft_is_separator(char *str, int i)
{
	if (i == 0 && str[i] == ';')
		return (1);
	else if (i > 0 && str[i - 1] != '\\' && str[i] == ';')
		return (1);
	return (0);
}

int			ft_is_token(int c)
{
	if (c != ' ' && c != '\t' && c != '\n')
		return (1);
	return (0);
}

int			ft_is_only_spaces(char *str)
{
	int		i;

	i = 0;
	while (str[i] && ft_isspace(str[i]) == 1)
		i++;
	if (!str[i])
		return (1);
	return (0);
}

int			ft_is_variable(char *str, int i, int quote)
{
	if (quote != '\''
	&& str[i] == '$' && str[i + 1]
	&& ((str[i + 1] >= 'a' && str[i + 1] <= 'z')
	|| (str[i + 1] >= 'A' && str[i + 1] <= 'Z')
	|| (str[i + 1] >= '0' && str[i + 1] <= '9')
	|| str[i + 1] == '_'))
		return (1);
	else if (quote != '\''
	&& str[i] == '$' && str[i + 1]
	&& str[i + 1] == '?')
		return (1);
	return (0);
}

int			ft_is_charset(char *str, int i)
{
	if ((str[i] >= 'a' && str[i] <= 'z')
	|| (str[i] >= 'A' && str[i] <= 'Z')
	|| (str[i] >= '0' && str[i] <= '9')
	|| str[i] == '_')
		return (1);
	if (str[i] == '?')
		return (1);
	return (0);
}

int			ft_need_expand(char *str)
{
	int		quote;
	int		i;

	quote = '\0';
	i = 0;
	while (str[i])
	{
		quote = ft_is_quote(str, i, quote);
		if (quote != '\'' && ft_is_variable(str, i, quote) == 1)
			return (1);
		i++;
	}
	return (0);
}
