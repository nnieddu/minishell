/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:02:01 by jobenass          #+#    #+#             */
/*   Updated: 2020/06/24 14:43:24 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*copy;
	unsigned int	len;
	unsigned int	i;

	copy = 0;
	len = ft_strlen(s);
	i = 0;
	if (!(copy = (char *)ft_calloc(len + 1, sizeof(char))))
		return (NULL);
	while (i < len && s[i])
	{
		copy[i] = (*f)(i, s[i]);
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
