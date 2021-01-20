/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:49:23 by jobenass          #+#    #+#             */
/*   Updated: 2020/06/24 14:42:21 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"

char	*ft_strchr(const char *s, int c)
{
	char	*p_s;
	int		i;

	p_s = (char *)s;
	i = 0;
	while (p_s[i] && p_s[i] != (char)c)
		i++;
	if (p_s[i] == (char)c)
		return (&p_s[i]);
	return (NULL);
}
