/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 20:22:54 by jobenass          #+#    #+#             */
/*   Updated: 2020/06/24 14:42:10 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;
	int				res;
	int				signe;

	signe = 1;
	if (n < 0)
	{
		write(fd, "-", 1);
		signe = -1;
	}
	res = 0;
	nb = n * signe;
	if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
		res = (nb % 10) + 48;
		write(fd, &res, 1);
	}
	if (nb <= 9)
	{
		res = (nb % 10) + 48;
		write(fd, &res, 1);
	}
}
