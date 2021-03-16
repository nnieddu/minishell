/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabstrlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 14:43:51 by jobenass          #+#    #+#             */
/*   Updated: 2021/02/18 08:15:23 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "./libft_update.h"

int		ft_tabstrlen(char **tab)
{
	int	i;

	if (!tab || !*tab)
		return (-1);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}
