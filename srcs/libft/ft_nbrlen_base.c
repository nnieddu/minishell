/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 12:57:27 by jobenass          #+#    #+#             */
/*   Updated: 2020/06/24 14:41:57 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"

int		ft_nbrlen_base(const char *base, int n, int signe)
{
	unsigned int	nb;
	unsigned int	len;
	size_t			size;

	len = 0;
	size = ft_strlen(base);
	if (n < 0 && signe == 1 && signe--)
		len++;
	if (n > 0 && signe == 1 && signe--)
		len++;
	if (n == 0)
		len++;
	nb = n;
	while (nb)
	{
		nb /= size;
		len++;
	}
	return (len);
}
