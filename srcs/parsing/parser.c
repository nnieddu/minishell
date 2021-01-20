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

static void	ft_for_next_step(int *id, int number, int *i)
{
	if (*id >= 0 && *id < (number - 1))
		(*id)++;
	else
		*id = -1;
	(*i)++;
}

static void	ft_clean_arguments(char ***arguments)
{
	if (!*arguments)
		return ;
	free(*arguments);
	*arguments = 0;
}

void		ft_clean_parser(t_parser **psr, int number)
{
	if (!*psr)
		return ;
	ft_clean_arguments(&(*psr)->arguments);
	ft_tabnbrdel(&(*psr)->tube, number);
	free(*psr);
	*psr = 0;
}

static int	ft_prepare_parser(t_mini **shl, int *id, int *i)
{
	if (ft_edit_variable(*shl, (*shl)->lxr->token) == EXIT_FAILURE
	|| ft_edit_token((*shl)->lxr->token) == EXIT_FAILURE
	|| !((*shl)->psr = malloc(sizeof(t_parser))))
		return (EXIT_FAILURE);
	ft_bzero((*shl)->psr, sizeof(t_parser));
	*id = -1;
	*i = 0;
	return (EXIT_SUCCESS);
}

int			ft_parser(t_mini *shl, int ret)
{
	int		number;
	int 	id;
	int		i;

	if ((ft_prepare_parser(&shl, &id, &i) == EXIT_FAILURE)
	|| ((number = ft_count_sequence(shl->lxr->token)) > 1
	&& !(shl->psr->tube = ft_set_pipes(number - 1))))
		return (EXIT_FAILURE);
	if (shl->psr->tube)
		id = 0;
	while (shl->lxr->token && shl->lxr->token[i])
	{
		if (ft_get_redirection(shl, i, id) == EXIT_FAILURE
		|| ft_get_conponents(shl->lxr->token, \
		&shl->psr->arguments, &i) == EXIT_FAILURE
		|| (ret = ft_executer(shl, number, id, ret)) != 0)
			break ;
		if (ft_strcmp(shl->lxr->token[i], "|") == 0)
			ft_for_next_step(&id, number, &i);
		ft_clean_arguments(&shl->psr->arguments);
	}
	ft_clean_parser(&shl->psr, number);
	return (ret);
}
