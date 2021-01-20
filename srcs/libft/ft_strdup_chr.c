/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_chr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 14:42:49 by jobenass          #+#    #+#             */
/*   Updated: 2020/06/24 14:42:52 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"

char	*ft_strdup_chr(const char *s1, int c)
{
	char	*res_dup;
	int		size;
	int		i;

	res_dup = 0;
	size = -1;
	if ((int)ft_strlen_chr((const char *)s1, c) != -1)
		size = (int)ft_strlen_chr((const char *)s1, c);
	if (size == -1 || !(res_dup = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		res_dup[i] = s1[i];
		i++;
	}
	res_dup[i] = '\0';
	return (res_dup);
}
