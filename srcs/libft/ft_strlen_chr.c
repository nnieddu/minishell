/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_chr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 14:43:20 by jobenass          #+#    #+#             */
/*   Updated: 2020/06/24 14:43:21 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"

size_t	ft_strlen_chr(const char *s, int c)
{
	size_t	len;

	len = 0;
	if (s)
	{
		while (s[len] && s[len] != c)
			len++;
		return (len);
	}
	return ((int)-1);
}
