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

int		ft_error(char *message, /*char *token, */char *custom)
{
	if ((errno != 0 || custom != NULL))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		// ft_putstr_fd(token, STDERR_FILENO);
		ft_putstr_fd(message, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		if (custom != NULL)
			ft_putendl_fd(custom, STDERR_FILENO);
		else if (errno != 0)
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}