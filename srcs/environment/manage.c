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

char	*ft_manage_shlvl(char *shlvl)
{
	char	*content;
	int		nbr;
	int		str;
	int		value;
	char	*tmp;

	content = ft_strchr(shlvl, '=');
	if (content)
		content++;
	nbr = 0;
	while (content && content[nbr] && ft_isdigit(content[nbr]) == 1)
		nbr++;
	str = 0;
	while (content && content[str])
		str++;
	if (nbr != str)
		return (strdup("SHLVL=1"));
	value = ft_atoi(content) + 1;
	tmp = ft_itoa(value);
	if (!tmp)
		return (NULL);
	content = ft_strjoin("SHLVL=", tmp);
	ft_strdel(&tmp);
	return (content);
}

int		ft_manage_underscore(char **envs, char **arguments)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (envs[i] && ft_strcmp_chr(envs[i], "_=", '=') != 0)
		i++;
	tmp = NULL;
	if (envs[i])
	{
		j = 0;
		while (arguments && arguments[j + 1])
			j++;
		tmp = envs[i];
		envs[i] = ft_strjoin("_=", arguments[j]);
		ft_strdel(&tmp);
		if (!envs[i])
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int		ft_manage_code(char **envs, int err)
{
	int		i;
	char	*tmp;
	char	*value;

	i = 0;
	while (envs[i] && ft_strcmp_chr(envs[i], "?=", '=') != 0)
		i++;
	tmp = NULL;
	value = NULL;
	if (envs[i])
	{
		tmp = envs[i];
		value = ft_itoa(err);
		if (!value)
			return (EXIT_FAILURE);
		envs[i] = ft_strjoin("?=", value);
		ft_strdel(&tmp);
		ft_strdel(&value);
		if (!envs[i])
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}