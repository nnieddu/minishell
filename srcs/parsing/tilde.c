/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:03:17 by jobenass          #+#    #+#             */
/*   Updated: 2021/03/12 09:42:39 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		ft_edit_tilde(t_mini *shl, char **token)
{
	char	*tmp;

	if (*token == NULL)
		return (EXIT_SUCCESS);
	tmp = NULL;
	if (token[0][0] == '~'
	&& (!token[0][1] || (token[0][1] && token[0][1] == '/')))
	{
		tmp = *token;
		if (!(*token = ft_strjoin(shl->home, &(token[0][1]))))
		{
			*token = tmp;
			return (EXIT_ERROR);
		}
		ft_strdel(&tmp);
	}
	return (EXIT_SUCCESS);
}
