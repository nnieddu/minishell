/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobenass <jobenass@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 08:06:23 by jobenass          #+#    #+#             */
/*   Updated: 2020/10/16 15:05:48 by jobenass         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_update.h"

static int		ft_countword(const char *str, char c)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	if (!str[i])
		count = 0;
	else if (str[0] != c)
		count++;
	while (str[i] != '\0')
	{
		if (str[i] == c && str[i + 1] != c && str[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

static char		*ft_strings(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i] == c && str[i + 1] != '\0')
		i++;
	str = &str[i];
	return (str);
}

static int		ft_lenword(char *str, char c)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (str[i] != c && str[i] != '\0')
	{
		count++;
		i++;
	}
	return (count);
}

static char		*ft_split_suit(char *str, char c, char **addr, int i)
{
	int		j;
	int		k;

	k = 0;
	if (!(addr[i] = (char *)ft_calloc(ft_lenword(str, c) + 1, sizeof(char))))
	{
		while (k < i)
			free(addr[k++]);
		free(addr);
		return (NULL);
	}
	j = 0;
	while (j < ft_lenword(str, c) && str[j])
	{
		addr[i][j] = str[j];
		j++;
	}
	addr[i][j] = '\0';
	return (addr[i]);
}

char			**ft_split(char const *s, char c)
{
	char	**tab;
	char	*str;
	int		i;
	int		k;

	str = (char *)s;
	tab = 0;
	if (!(tab = (char **)ft_calloc(ft_countword(s, c) + 1, sizeof(char *))))
		return (NULL);
	i = 0;
	while (i < ft_countword(s, c))
	{
		k = 0;
		str = ft_strings(str, c);
		if (!(tab[i] = ft_split_suit(str, c, tab, i)))
			return (NULL);
		while (str[k] && str[k] != c)
			k++;
		str = &str[k + 1];
		i++;
	}
	tab[i] = 0;
	return (tab);
}
