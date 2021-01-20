/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:09:17 by jobenass          #+#    #+#             */
/*   Updated: 2020/06/24 14:41:20 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p_s;
	size_t			i;

	p_s = 0;
	i = 0;
	if (n >= 1)
	{
		p_s = s;
		while (i < n)
			p_s[i++] = 0;
	}
}
