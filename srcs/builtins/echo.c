////////////////////////////////////////////////////////////////////////////////
//
// 		███    ██  ██████  ████████ ███████ ███████ 
// 		████   ██ ██    ██    ██    ██      ██      
// 		██ ██  ██ ██    ██    ██    █████   ███████ 
// 		██  ██ ██ ██    ██    ██    ██           ██ 
// 		██   ████  ██████     ██    ███████ ███████ 
//
//		Doit afficher les " et pas \" dans "test\""
//
////////////////////////////////////////////////////////////////////////////////

#include "../../incs/minishell.h"

int		ft_cmd_echo(char **args, int out)
{
	int		nonewline;
	int		index;

	nonewline = 0;
	index = 1;
	if (args[index] && ft_strcmp(args[index], "-n") == 0)
		nonewline = 1;
	if (nonewline == 1)
		index++;
	while (args && args[index])
	{
		ft_putstr_fd(args[index], out);
		if (((nonewline == 0 && index >= 1) || (nonewline == 1 && index >= 2))
		&& args[index + 1])
			ft_putchar_fd(' ', out);
		index++;
	}
	if (nonewline != 1)
		ft_putchar_fd('\n', out);
	return (ft_error("echo", NULL));
}