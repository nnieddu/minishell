/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_idx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 10:01:28 by jobenass          #+#    #+#             */
/*   Updated: 2020/11/28 14:16:40 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"

char 	*ft_strdup_idx(const char *s1, int ind)
{
	char	*res_dup;
	int		j;

	res_dup = 0;
	if (ind < 0 || !(res_dup = malloc(sizeof(char) * (ind + 1))))
		return (NULL);
	j = -1;
	while (++j < ind)
		res_dup[j] = s1[j];
	res_dup[j] = '\0';
	return (res_dup);
}