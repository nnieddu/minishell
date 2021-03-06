/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 07:56:02 by jobenass          #+#    #+#             */
/*   Updated: 2021/02/18 08:14:54 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"

void	ft_putendl(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		write(0, &s[i++], 1);
	write(0, "\n", 1);
}
