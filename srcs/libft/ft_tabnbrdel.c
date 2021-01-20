/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabnbrdel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 14:43:48 by jobenass          #+#    #+#             */
/*   Updated: 2020/12/16 15:14:26 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "./libft_update.h"

void 	ft_tabnbrdel(int ***tab, int size)
{
	int		i;
	
	if (!tab || !*tab)
		return ;
	i = 0;
	while (i < size - 1)
	{
		if ((*tab)[i])
			free((*tab)[i]);
		(*tab)[i] = NULL;
		i++;
	}
	free(*tab);
	*tab = 0;
}