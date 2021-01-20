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

void	ft_crash(t_mini **shl, t_list **list, int number)
{
	if (list)
		ft_clean_list(list);
	if (shl && (*shl)->psr)
		ft_clean_parser(&(*shl)->psr, number);
	if (shl && (*shl)->lxr)
		ft_clean_lexer(&(*shl)->lxr);
	if (shl)
		ft_clean_general(shl);
	// err = -1;
	ft_putstr_fd("¯\\_(ツ)_/¯ ", STDERR_FILENO);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd("Has encountered an error and must stop", STDERR_FILENO);
	exit(1);
}