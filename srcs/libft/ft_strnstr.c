/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:55:33 by jobenass          #+#    #+#             */
/*   Updated: 2020/06/24 14:43:32 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	l_needle;
	size_t	i;
	size_t	j;

	if (needle[0] == 0)
		return ((char *)haystack);
	l_needle = ft_strlen(needle);
	i = 0;
	while (i < len && haystack[i])
	{
		j = 0;
		if (haystack[i] == needle[0])
		{
			while (haystack[i + j] && needle[j]
				&& (needle[j] == haystack[i + j])
				&& j < l_needle && i + j < len)
				j++;
			if (j == l_needle)
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (0);
}
