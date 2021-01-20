/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 10:01:28 by jobenass          #+#    #+#             */
/*   Updated: 2020/06/24 14:41:22 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;

	ptr = 0;
	if (!(ptr = malloc(size * count)))
		return (NULL);
	ft_bzero(ptr, (size * count));
	return (ptr);
}
