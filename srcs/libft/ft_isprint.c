/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:27:52 by jobenass          #+#    #+#             */
/*   Updated: 2020/06/24 14:41:35 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"

int		ft_isprint(int c)
{
	if (c >= ' ' && c <= '~')
		return (1);
	return (0);
}
