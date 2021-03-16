/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_idx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 07:22:40 by jobenass          #+#    #+#             */
/*   Updated: 2021/02/18 08:15:11 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"
#include <stdio.h>

char	*ft_strjoin_idx(char const *s1, char const *s2, int ind)
{
	char	*res_join;
	int		size;
	int		i;
	int		j;

	size = (int)ft_strlen(s1);
	res_join = 0;
	if (size == -1 || ind < 0
	|| !(res_join = malloc(sizeof(char) * (size + ind + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j] && i < size)
		res_join[i++] = s1[j++];
	j = 0;
	while (s2[j] && j < ind && i < (size + ind))
		res_join[i++] = s2[j++];
	res_join[i] = '\0';
	return (res_join);
}
