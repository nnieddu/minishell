/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 23:28:31 by jobenass          #+#    #+#             */
/*   Updated: 2020/06/05 19:44:29 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"

void	ft_strclr(char *s)
{
	char	*ptr;
	int		i;

	if (!s)
		return ;
	ptr = s;
	i = 0;
	while (s[i])
		ptr[i] = 0;
	ptr[i] = 0;
}
