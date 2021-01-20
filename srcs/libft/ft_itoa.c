/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 18:34:02 by jobenass          #+#    #+#             */
/*   Updated: 2020/06/24 14:41:41 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"

static int	ft_nblen(int n)
{
	unsigned int		len;

	len = 0;
	if (n <= 0)
	{
		len++;
		n = n * -1;
	}
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	char			*str;
	char			minus;
	unsigned int	nb;
	unsigned int	len;

	str = 0;
	minus = '-';
	if (n < 0)
		nb = n * -1;
	else
		nb = n;
	len = ft_nblen(n);
	if (!(str = (char *)ft_calloc(len + 1, sizeof(char))))
		return (NULL);
	str[len] = '\0';
	if (n == 0)
		str[--len] = '0';
	while (nb)
	{
		str[--len] = (nb % 10) + 48;
		nb = nb / 10;
	}
	if (n < 0)
		str[0] = minus;
	return (str);
}
