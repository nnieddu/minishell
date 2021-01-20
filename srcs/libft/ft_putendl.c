#include "libft_update.h"

void	ft_putendl(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		write(0, &s[i++], 1);
	write(0, "\n", 1);
}
