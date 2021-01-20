/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:59:44 by jobenass          #+#    #+#             */
/*   Updated: 2020/06/24 14:43:42 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p_s;
	char	*copy;
	size_t	size;
	size_t	i;

	i = 0;
	p_s = 0;
	size = ft_strlen((char *)s);
	if (start < size)
		p_s = (char *)&s[(size_t)start];
	else
		p_s = (char *)&s[ft_strlen(s)];
	size = 0;
	while (p_s[size] && size < len)
		size++;
	if (!(copy = (char *)ft_calloc(size + 1, sizeof(char))))
		return (NULL);
	while (i < size && p_s[i])
	{
		copy[i] = p_s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
