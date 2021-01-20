#include "../../incs/minishell.h"

char	*ft_get_env(char **env, char *key)
{
	char	*var;
	int		i;

	if (!env)
		return (NULL);
	var = ft_strjoin(key, "=");
	i = -1;
	while (env[++i] && var)
		if (ft_strcmp_chr(env[i], var, '=') == 0)
			break ;
	ft_strdel(&var);
	if (env[i])
		return (ft_strchr(env[i], '=') + 1);
	return (NULL);
}

char	**ft_list_to_tab(t_list *list)
{
	char	**token;
	int		len;
	int		i;

	token = 0;
	len = ft_list_size(list);
	if (!(token = malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		token[i] = ft_strdup(list->content);
		if (!token[i])
		{
			ft_tabstrdel(&token);
			return (NULL);
		}
		list = list->next;
		i++;
	}
	token[i] = 0;
	return (token);
}

char	*ft_join_path(char *dir, char *command)
{
	char	*binary;
	char	*path;

	if (dir[ft_strlen(dir) - 1] != '/')
		path = ft_strjoin(dir, "/");
	else
		path = ft_strdup(dir);
	if (!path)
		return (NULL);
	binary = ft_strjoin(path, command);
	ft_strdel(&path);
	return (binary);
}