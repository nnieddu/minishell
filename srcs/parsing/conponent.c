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

int		ft_count_sequence(char **token)
{
	int		index;
	int		count;

	count = 0;
	index = -1;
	while (token[++index])
		if (ft_strcmp(token[index], "|") == 0)
			count++;
	return (count + 1);
}

int		**ft_set_pipes(int number)
{
	int		index;
	int		**tube;

	if (number == 0 || !(tube = malloc(sizeof(int *) * number)))
		return (NULL);
	ft_bzero(tube, sizeof(int *) * number);
	index = 0;
	while (tube && index < number)
	{
		tube[index] = malloc(sizeof(int) * 2);
		if (tube[index] == NULL)
		{
			ft_tabnbrdel(&tube, index);
			return (NULL);
		}
		tube[index][IN] = -1;
		tube[index][OUT] = -1;
		index++;
	}
	return (tube);
}

int		ft_get_conponents(char **token, char ***arguments, int *i)
{
	int		size;
	int		tmp;

	size = 0;
	tmp = *i;
	while (token && token[tmp] && ft_strcmp(token[tmp], "|") != 0)
	{
		if (ft_strcmp(token[tmp], "") != 0)
			size++;
		tmp++;
	}
	(*arguments) = malloc(sizeof(char *) * (size + 1));
	if (!(*arguments))
		return (EXIT_FAILURE);
	tmp = 0;
	while (token && token[*i] && ft_strcmp(token[*i], "|") != 0)
	{
		if (ft_strcmp(token[*i], "") != 0)
			(*arguments)[tmp++] = token[*i];
		(*i)++;
	}
	(*arguments)[tmp] = NULL;
	return (EXIT_SUCCESS);
}
