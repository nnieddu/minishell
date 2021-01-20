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

// static void	ft_sort_env(char ***tab)
// {
// 	char	*tmp;
// 	int		index;

// 	index = 0;
// 	while ((*tab)[index])
// 	{
// 		if ((*tab)[index + 1]
// 		&& ft_strcmp((*tab)[index], (*tab)[index + 1]) > 0)
// 		{
// 			tmp = (*tab)[index];
// 			(*tab)[index] = (*tab)[index + 1];
// 			(*tab)[index + 1] = tmp;
// 			index = -1;
// 		}
// 		index++;
// 	}
// }

// static int	ft_print_env(t_vars *env)
// {
// 	char	**tab;
// 	int		index;

// 	tab = 0;
// 	if (!(tab = ft_env_to_tab(env)))
// 		return (EXIT_FAILURE);
// 	ft_sort_env(&tab);
// 	index = 0;
// 	while (tab[index])
// 	{
// 		if (ft_strcmp(tab[index], "_") != 0)
// 			ft_export_print(tab[index], env);
// 		index++;
// 	}
// 	ft_clean_tab(&tab);
// 	return (EXIT_SUCCESS);
// }

// static int	ft_append_env(t_vars *env, char *key, char egal, char *value)
// {
// 	t_vars	*search;

// 	search = env;
// 	while (search && ft_strcmp(search->key, key) != 0)
// 		search = search->next;
// 	if (!search)
// 	{
// 		if (!(search = ft_create_env(key, egal, value)))
// 			return (EXIT_FAILURE);
// 		ft_add_env(&env, search);
// 	}
// 	else
// 	{
// 		ft_strdel(&(search)->value);
// 		search->value = ft_strdup(value);
// 		if (egal == '=' && search->operand == '\0')
// 			search->operand = egal;
// 		if (!search->value)
// 			return (EXIT_FAILURE);
// 	}
// 	return (EXIT_SUCCESS);
// }

// static int	ft_get_data(char *arg, char **key, char *egal, char **value)
// {
// 	int		error;
// 	int		index;

// 	error = 0;
// 	index = 0;
// 	if (ft_isdigit(arg[index]) == 1)
// 		error = 1;
// 	while (error == 0 && arg[index] && arg[index] != '='
// 	&& (ft_isalnum(arg[index]) == 1 || arg[index] == '_'))
// 		index++;
// 	if (error == 1 || ft_isspace(arg[index]) == 1
// 	|| (ft_isalnum(arg[index]) == 0 && arg[index] != '\0' && arg[index] != '='))
// 		ft_putendl("not a valid identifier");
// 	if (error == 1 || !(*key = ft_strdup_idx(arg, index)))
// 		return (EXIT_FAILURE);
// 	if (arg[index] == '=')
// 		*egal = arg[index++];
// 	if (key
// 	&& ((*egal == '=' && !(*value = ft_strdup(&arg[index])))
// 	|| (*egal != '=' && !(*value = ft_strdup("")))))
// 	{
// 		ft_strdel(key);
// 		return (EXIT_FAILURE);
// 	}
// 	return (EXIT_SUCCESS);
// }

// int			ft_cmd_export(char **args, char ***env)
// {
// 	char	*key;
// 	char	egal;
// 	char	*value;
// 	int		index;

// 	key = 0;
// 	value = 0;
// 	index = 1;
// 	// if (!args[index])
// 	// 	return (ft_print_env(*envs));
// 	while (args[index])
// 	{
// 		egal = '\0';
// 		if (ft_get_data(args[index], &key, &egal, &value) == EXIT_FAILURE
// 		|| ft_append_env(env, key, egal, value) == EXIT_FAILURE)
// 			return (EXIT_FAILURE);
// 		ft_strdel(&key);
// 		ft_strdel(&value);
// 		index++;
// 	}
// 	return (EXIT_SUCCESS);
// }

int			ft_cmd_export(char **args, char ***env)
{
	(void)args;
	(void)env;
	
	return (EXIT_SUCCESS);
}