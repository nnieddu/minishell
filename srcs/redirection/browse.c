////////////////////////////////////////////////////////////////////////////////
//
// 		███    ██  ██████  ████████ ███████ ███████ 
// 		████   ██ ██    ██    ██    ██      ██      
// 		██ ██  ██ ██    ██    ██    █████   ███████ 
// 		██  ██ ██ ██    ██    ██    ██           ██ 
// 		██   ████  ██████     ██    ███████ ███████ 
//
//		INFO: (gérer les petits cas de merde)
//			bin/cat < Z/write
//
////////////////////////////////////////////////////////////////////////////////

#include "../../incs/minishell.h"

static int	ft_access_directory(char *path)
{
	struct stat		info;
	int				access;
	DIR				*directory;

	directory = NULL;
	access = stat(path, &info);
	if (access == 0 && S_ISDIR(info.st_mode) == 1)
		if ((directory = opendir(path)) != NULL)
			closedir(directory);
	return (errno == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}

static int	ft_access_file(char *operand, char *path)
{
	struct stat		info;
	int				access;
	int				file;

	file = -1;
	access = stat(path, &info);
	if (access == 0 && S_ISREG(info.st_mode) == 0)
	{
		if (ft_access_directory(path) == EXIT_SUCCESS)
			file = open(path, O_WRONLY, S_IRWXU);
	}
	else
	{
		if (access == -1)
			errno = 0;
		if (ft_strcmp(operand, "<") == 0)
			file = open(path, O_RDONLY, S_IRWXU);
		else if (ft_strcmp(operand, ">") == 0)
			file = open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
		else if (ft_strcmp(operand, ">>") == 0)
			file = open(path, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	}
	return (file);
}

static char	*ft_add_parts(char *input, int *length, char **path)
{
	char	*tmp;

	if (input[*length] == '/')
			(*length)++;
	if (!*path && !(*path = ft_strdup("")))
		return (NULL);
	tmp = *path;
	*path = ft_strjoin_idx(tmp, input, *length);
	ft_strdel(&tmp);
	return (*path);
}

int			ft_browse_redirection(char *operand, char *input)
{
	int				index;
	int				length;
	char			*path;
	int				file;

	path = NULL;
	file = -1;
	index = 0;
	while (input[index] && errno == 0)
	{
		length = ft_strlen_chr(&input[index], '/');
		path = ft_add_parts(&input[index], &length, &path);
		index += length;
		if (!input[index])
			break ;
		ft_access_directory(path);
	}
	if (errno == 0)
		file = ft_access_file(operand, path);
	ft_strdel(&path);
	return (file);
}
