/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:50:52 by jobenass          #+#    #+#             */
/*   Updated: 2020/06/24 14:41:42 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*p_dst;
	unsigned char	*p_src;
	size_t			i;

	p_dst = 0;
	p_src = 0;
	i = 0;
	if (n >= 1 && (dst || src))
	{
		p_dst = dst;
		p_src = (unsigned char *)src;
		while (i < n)
		{
			p_dst[i] = p_src[i];
			if (p_dst[i] == (unsigned char)c)
				return (&p_dst[i + 1]);
			i++;
		}
	}
	return (NULL);
}
