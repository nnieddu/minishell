/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:01:26 by jobenass          #+#    #+#             */
/*   Updated: 2021/02/18 08:12:09 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		ft_cmd_pwd(int out)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (EXIT_ERROR);
	ft_putendl_fd(pwd, out);
	ft_strdel(&pwd);
	return (EXIT_SUCCESS);
}
