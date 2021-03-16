/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 12:10:52 by jobenass          #+#    #+#             */
/*   Updated: 2020/06/24 14:42:06 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"

void	ft_putnbr_base(const char *base, int n, int signe)
{
	unsigned int	nb;
	size_t			size;

	if (n < 0 && signe == 1 && signe--)
		ft_putchar('-');
	if (n > 0 && signe == 1 && signe--)
		ft_putchar('+');
	nb = n;
	size = ft_strlen(base);
	if (nb >= size)
	{
		ft_putnbr_base(base, nb / size, signe);
		ft_putchar(base[nb % (int)size]);
	}
	if (nb < size)
		ft_putchar(base[nb]);
}
