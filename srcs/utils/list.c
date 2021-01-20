#include "../../incs/minishell.h"

int		ft_list_size(t_list *list)
{
	int		len;

	len = 0;
	while (list)
	{
		list = list->next;
		len++;
	}
	return (len);
}

t_list		*ft_create_item(char *content)
{
	t_list	*new;

	new = 0;
	if (!(new = malloc(sizeof(t_list) * 1)))
		return (NULL);
	ft_bzero(new, sizeof(t_list) * 1);
	new->content = ft_strdup(content);
	new->next = NULL;
	return (new);
}

void		ft_add_item(t_list **list, t_list *new)
{
	t_list	*tmp;

	tmp = *list;
	if (!new || !list)
		return ;
	if (!*list)
		*list = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void		ft_clean_list(t_list **list)
{
	t_list	*tmp;

	tmp = NULL;
	if (!list || !*list)
		return ;
	while (*list)
	{
		tmp = *list;
		(*list) = (*list)->next;
		ft_strdel(&tmp->content);
		tmp->next = NULL;
		free(tmp);
		tmp = NULL;
	}
	list = NULL;
}