/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 10:58:44 by jobenass          #+#    #+#             */
/*   Updated: 2020/06/24 14:43:40 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"

static int		ft_setornot(char c, char const *set)
{
	int		i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*copy;
	int		start;
	int		end;
	int		i;

	copy = 0;
	start = 0;
	end = ft_strlen(s1);
	i = 0;
	while (ft_setornot(s1[start], set) == 1)
		start++;
	while (end > start && ft_setornot(s1[end - 1], set) == 1)
		end--;
	end = end - start;
	if (!(copy = (char *)ft_calloc(end + 1, sizeof(char))))
		return (NULL);
	while (i < end && s1[start])
		copy[i++] = s1[start++];
	copy[i] = 0;
	return (copy);
}
