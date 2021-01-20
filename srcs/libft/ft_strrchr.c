/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 10:18:29 by jobenass          #+#    #+#             */
/*   Updated: 2020/06/24 14:43:37 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*p_s;
	int		i;
	int		present;

	p_s = (char *)s;
	present = 0;
	i = 0;
	while (p_s[i])
	{
		if (p_s[i] == (char)c)
			present = 1;
		i++;
	}
	while (p_s[i] != (char)c && i >= 0 && present == 1)
		i--;
	if (p_s[i] == (char)c)
		return (&p_s[i]);
	return (NULL);
}
