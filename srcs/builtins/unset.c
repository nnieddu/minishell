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

static int	ft_is_correct(char *args)
{
	int		index;

	index = 1;
	if (ft_isdigit(args[0]) == 1)
		return (EXIT_FAILURE);
	while (args && args[index]
	&& (ft_isalnum(args[index]) == 1 || args[index] == '_'))
		index++;
	if (args[index])
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static char	**ft_rebuild_variables(char *var, char **envs)
{
	int		size;
	int		in;
	int		out;
	char	**new;

	size = 0;
	while (envs[size])
		size++;
	if (!(new = malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	in = 0;
	out = 0;
	while (envs[in])
	{
		if (ft_strcmp_chr(envs[in], var, '=') != 0
		&& !(new[out++] = ft_strdup(envs[in])))
		{
			ft_tabstrdel(&new);
			break ;
		}
		in++;
	}
	if (new)
		new[out] = NULL;
	return (new);
}

static int	ft_delete(char *key, char ***envs)
{
	int		index;
	char	*del;
	char	**new;

	new = 0;

	del = ft_strjoin(key, "=");
	index = -1;
	while ((*envs)[++index])
		if (ft_strcmp_chr((*envs)[index], del, '=') == 0)
			break ;
	if ((*envs)[index])
	{
		new = ft_rebuild_variables(del, *envs);
		ft_tabstrdel(envs);
		*envs = new;
	}
	ft_strdel(&del);
	return (*envs != NULL ? EXIT_SUCCESS : EXIT_FAILURE);
}

int			ft_cmd_unset(char **args, char ***envs)
{
	int		index;
	int		error;

	error = 0;
	index = 1;
	while (args[index])
	{
		if ((error = ft_is_correct(args[index])) == EXIT_SUCCESS)
		{
			if (ft_delete(args[index], envs) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else
			return (ft_error("unset", "Not a valid identifier"));
		index++;
	}
	return (ft_error("unset", NULL));
}