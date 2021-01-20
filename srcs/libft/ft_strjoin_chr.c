/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_chr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninieddu <ninieddu@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 14:43:05 by jobenass          #+#    #+#             */
/*   Updated: 2020/12/03 12:38:07 by ninieddu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"

char	*ft_strjoin_chr(char const *s1, int c, char const *s2, int d)
{
	char	*res_join;
	int		size;
	int		i;
	int		j;

	res_join = 0;
	size = -1;
	if ((int)ft_strlen_chr(s1, c) != -1 && (int)ft_strlen_chr(s2, d) != -1)
		size = (int)ft_strlen_chr(s1, c) + (int)ft_strlen_chr(s2, d);
	if (size == -1 || !(res_join = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j] && i < (int)ft_strlen_chr(s1, c) && i < size)
		res_join[i++] = s1[j++];
	j = 0;
	while (s2[j] && j < (int)ft_strlen_chr(s2, d) && i < size)
		res_join[i++] = s2[j++];
	res_join[i] = '\0';
	return (res_join);
}
