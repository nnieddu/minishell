/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabstrclr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 14:41:00 by jobenass          #+#    #+#             */
/*   Updated: 2020/12/19 20:09:30 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "./libft_update.h"

void	ft_tabstrclr(char **tab)
{
	int	i;
	int	j;

	if (!tab || !*tab)
		return ;
	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			tab[i][j] = '\0';
			j++;
		}
	}
}