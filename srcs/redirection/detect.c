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

static int	ft_clear_tokens(char **token, int i)
{
	ft_strdel(&token[i]);
	ft_strdel(&token[i + 1]);
	token[i] = ft_strnew(1);
	token[i + 1] = ft_strnew(1);
	if (!token[i] || !token[i + 1])
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_get_file(char *operand, char *input, int *fd)
{
	int		*file;

	file = NULL;
	if (ft_strcmp(operand, "<") == 0)
		file = &fd[IN];
	else if (ft_strcmp(operand, ">") == 0 || ft_strcmp(operand, ">>") == 0)
		file = &fd[OUT];
	if (file != NULL)
		*file = ft_browse_redirection(operand, input);
	ft_error(input, NULL);														// voir value
	return (*file != -1 ? EXIT_SUCCESS : EXIT_FAILURE);
}

static int	ft_get_pipe(int *tube)
{
	int		ret;

	ret = pipe(tube);
	ft_error("pipe", NULL);														// voir value
	return (ret != -1 ? EXIT_SUCCESS : EXIT_FAILURE);
}

static int	ft_get_type(char **token, int i, int id)
{
	if (token[i + 1] && (ft_strcmp(token[i], "<") == 0
	|| ft_strcmp(token[i], ">") == 0 || ft_strcmp(token[i], ">>") == 0))
		return (1);
	else if (id != -1 && ft_strcmp(token[i], "|") == 0)
		return (2);
	return (0);
}

int			ft_get_redirection(t_mini *shl, int i, int id)
{
	int		type;

	shl->psr->fd[IN] = STDIN_FILENO;
	shl->psr->fd[OUT] = STDOUT_FILENO;
	while (shl->lxr->token && shl->lxr->token[i])
	{
		type = ft_get_type(shl->lxr->token, i, id);
		if (type == 1)
		{
			if (ft_get_file(shl->lxr->token[i], shl->lxr->token[i + 1], \
			shl->psr->fd) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			ft_clear_tokens(shl->lxr->token, i);
			i++;
		}
		else if (type == 2)
		{
			if (ft_get_pipe(shl->psr->tube[id]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			break ;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
