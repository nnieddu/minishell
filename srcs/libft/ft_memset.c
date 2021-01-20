/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 08:22:29 by jobenass          #+#    #+#             */
/*   Updated: 2020/06/24 14:41:53 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p_b;
	size_t			i;

	p_b = 0;
	i = 0;
	if (len >= 1)
	{
		p_b = b;
		while (i < len)
			p_b[i++] = (unsigned char)c;
	}
	return (b);
}
