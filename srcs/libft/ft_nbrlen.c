/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 13:34:02 by jobenass          #+#    #+#             */
/*   Updated: 2020/06/24 14:41:56 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"

int		ft_nbrlen(int n)
{
	unsigned int	nb;
	unsigned int	len;

	len = 0;
	if (n < 0)
		n *= -1;
	if (n == 0)
		len++;
	nb = n;
	while (nb)
	{
		nb /= 10;
		len++;
	}
	return (len);
}
