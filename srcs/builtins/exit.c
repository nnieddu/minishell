////////////////////////////////////////////////////////////////////////////////
//
// 		███    ██  ██████  ████████ ███████ ███████ 
// 		████   ██ ██    ██    ██    ██      ██      
// 		██ ██  ██ ██    ██    ██    █████   ███████ 
// 		██  ██ ██ ██    ██    ██    ██           ██ 
// 		██   ████  ██████     ██    ███████ ███████ 
//
//		Manque la gestion de $?
//		Doit set errno??
//
////////////////////////////////////////////////////////////////////////////////

#include "../../incs/minishell.h"

int		ft_get_last_ret(char *s1)
{
	int		len;
	int		i;
	int		x;
	char	*dup;

	dup = 0;
	i = 2;
	x = 0;
	len = ft_strlen(s1);
	if (!(dup = (char *)ft_calloc(len + 1, sizeof(char))))
		return (EXIT_FAILURE);
	while (s1[i] && i < len)
	{
		dup[x] = s1[i];
		i++;
		x++;
	}
	dup[x] = '\0';
	x = atoi(dup);
	free(dup);
	return (x);
}

int		ft_exit(t_mini *shl, int ret)
{
	int i;

	ft_putendl("exit");
	i = -1;
	if (!shl->psr->arguments[1])
	{
		while (shl->env && shl->env[++i])
			if (ft_strncmp(shl->env[i], "?=", 2) == 0)
				ret = ft_get_last_ret(shl->env[i]);
	}
	if (ft_is_first_time(shl) == 0)
	{
		ft_tabstrdel(&shl->psr->arguments);
		free(shl->psr);
		ft_clean_general(&shl);
		exit (ret);
	}
	shl->exit = 1;
	return (ret);
}

static int	ft_is_exit(char **args)
{
	int		index;

	if (args[0] && args[1] && args[2])
	{
		ft_error("exit", "Too many arguments");
		return (1); //	retourne 1
	}
	index = 0;
	while (args[1] && args[1][index]
	&& (args[1][0] == '-' || ft_isdigit(args[1][index]) == 1))
		index++;
	if (args[1] && args[1][index])
	{
		ft_error("exit", "Numeric argument required");
		return (255);	//	retourne 255
	}
	return (EXIT_SUCCESS);
}

static int	ft_manage_value(int value)
{
	if (value > 0)
		while (value > 0 && (value - 256) >= 0)
			value -= 256;
	else if (value < 0 &&  value > -256)
		while (value < 0  && value > -256 && (value + 256) >= 0)
			value += 256;
	else if (value < -256)
		while ((value) < 0)
			value += 256;
	return (value);
}

int		ft_cmd_exit(char **args)
{
	int		value;
	
	if ((value = ft_is_exit(args)) != EXIT_SUCCESS)
		return (value);
	if (args[1] && ft_strlen(args[1]) < 9)
	{
		value = ft_atoi(args[1]);
		value = ft_manage_value(value);
	}
	return (value);
}