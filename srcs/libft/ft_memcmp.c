/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:05:44 by jobenass          #+#    #+#             */
/*   Updated: 2020/06/24 14:41:46 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p_s1;
	unsigned char	*p_s2;
	size_t			i;

	p_s1 = 0;
	p_s2 = 0;
	i = 0;
	if (n >= 1)
	{
		p_s1 = (unsigned char *)s1;
		p_s2 = (unsigned char *)s2;
		while (i < n - 1 && p_s1[i] == p_s2[i])
			i++;
		if (p_s1[i] != p_s2[i])
			return (p_s1[i] - p_s2[i]);
	}
	return (0);
}
