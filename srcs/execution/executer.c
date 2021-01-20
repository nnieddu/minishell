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

int		ft_define_input(int *fd, int **pipe, int number, int id)
{
	if (fd[IN] != STDIN_FILENO)
		return (fd[IN]);
	if (pipe && id != -1)
		if (id > 0 && id <= (number - 1))
			return (pipe[id - 1][IN]);
	return (STDIN_FILENO);
}

int		ft_define_output(int *fd, int **pipe, int number, int id)
{
	if (fd[OUT] != STDOUT_FILENO)
	{
		if (pipe && id != -1 && id < (number - 1))
			close(pipe[id][OUT]);
		return (fd[OUT]);
	}
	if (pipe && id != -1)
		if (id >= 0 && id < (number - 1))
			return (pipe[id][OUT]);
	return (STDOUT_FILENO);
}

int		ft_executer(t_mini *shl, int number, int id, int err)
{
	int		in;
	int		out;

	in = ft_define_input(shl->psr->fd, shl->psr->tube, number, id);
	out = ft_define_output(shl->psr->fd, shl->psr->tube, number, id);
	if (ft_manage_underscore(shl->env, \
	shl->psr->arguments) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if ((shl->psr->command = ft_get_command(shl->env, \
	shl->psr->arguments)) == NULL)
	{
		ft_manage_code(shl->env, err); // Pour Jojo = penser a une autre facon de faire plus logique
		ft_error(shl->lxr->token[0], "Command not found");
		return (ft_set_ret(shl, "?=127")); // retour 'cmd not found' = 127, return en EXIT_SUCCESS pour pas casser la boucle de depart dans minishell.c
	}
	shl->psr->arguments[0] = shl->psr->command;
	if (ft_is_builtins(shl->psr->arguments[0]) == 1)
		err = ft_execute_builtins(shl, out);
	else
		err = ft_execute_binaries(shl, in, out);
	ft_manage_code(shl->env, err);
	ft_strdel(&shl->psr->command);
	return (err);
}