/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 18:53:07 by jobenass          #+#    #+#             */
/*   Updated: 2020/06/24 14:41:50 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*p_dst;
	unsigned char	*p_src;

	p_dst = 0;
	p_src = 0;
	if (len >= 1 && (dst || src))
	{
		p_dst = dst;
		p_src = (unsigned char *)src;
		if (src < dst)
		{
			while (len > 0)
			{
				p_dst[len - 1] = p_src[len - 1];
				len--;
			}
		}
		else
			dst = ft_memcpy(dst, src, len);
	}
	return (dst);
}
