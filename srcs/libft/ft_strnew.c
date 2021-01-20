/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 23:26:59 by jobenass          #+#    #+#             */
/*   Updated: 2020/06/05 19:44:34 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;

	str = 0;
	if (!(str = malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	i = 0;
	while (i < size)
		str[i++] = 0;
	str[i] = 0;
	return (str);
}
