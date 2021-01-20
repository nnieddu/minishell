/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:42:47 by jobenass          #+#    #+#             */
/*   Updated: 2020/06/24 14:42:18 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"

int		ft_give_the_good_string(const char *s, const char *set)
{
	int		ignored;

	ignored = 0;
	while (s[ignored] && ft_ischarset(s[ignored], set) == 1)
		ignored++;
	return (ignored);
}

int		ft_count(const char *s, const char *set, int option)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	if (option == 1 && s[0] && ft_ischarset(s[0], set) == 0)
		count++;
	while (option == 1 && s[i])
	{
		if (ft_ischarset(s[i], set) == 1 && (ft_ischarset(s[i + 1], set) == 0))
		{
			count++;
			if (!s[i + 1])
				count--;
		}
		i++;
	}
	while (option == 2 && s[count] && ft_ischarset(s[count], set) == 0)
		count++;
	return (count);
}

char	*ft_split_charset_suit(const char *s, const char *set)
{
	char	*res;
	int		lenght;
	int		i;

	lenght = ft_count(s, set, 2);
	res = 0;
	if (!(res = (char *)malloc(sizeof(char) * (lenght + 1))))
		return (NULL);
	i = 0;
	while (i < lenght)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

char	**ft_split_charset(const char *s, const char *set)
{
	char	**res;
	int		words;
	int		i;

	if (!s || !set)
		return (NULL);
	words = ft_count(s, set, 1);
	res = 0;
	if (!(res = (char **)malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	i = 0;
	while (i < words)
	{
		s = &s[ft_give_the_good_string(s, set)];
		res[i] = ft_split_charset_suit(s, set);
		s = &s[ft_count(s, set, 2)];
		i++;
	}
	res[i] = 0;
	return (res);
}
