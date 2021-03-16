/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:28:27 by jobenass          #+#    #+#             */
/*   Updated: 2020/06/24 14:41:44 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p_s;
	size_t			i;

	p_s = 0;
	i = 0;
	if (n >= 1)
	{
		p_s = (unsigned char *)s;
		while (i < n && p_s[i] != (unsigned char)c)
			i++;
		if (i >= n)
			return (NULL);
		p_s = (void *)&p_s[i];
	}
	return (p_s);
}
