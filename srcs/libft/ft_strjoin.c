/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 07:22:40 by jobenass          #+#    #+#             */
/*   Updated: 2020/06/24 14:42:57 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	size_t	i;
	size_t	j;
	size_t	k;
	char	*copy;

	copy = 0;
	i = 0;
	j = 0;
	k = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	if (!(copy = (char *)ft_calloc(size + 1, sizeof(char))))
		return (NULL);
	while (s1[i] && k < size)
		copy[k++] = s1[i++];
	while (s2[j] && k < size)
		copy[k++] = s2[j++];
	copy[k] = '\0';
	return (copy);
}
