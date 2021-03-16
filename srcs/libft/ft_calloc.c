/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninieddu <ninieddu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 10:01:28 by jobenass          #+#    #+#             */
/*   Updated: 2021/02/18 10:39:29 by ninieddu         ###   ########lyon.fr   */
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
