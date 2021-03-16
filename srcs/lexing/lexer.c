/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninieddu <ninieddu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:02:20 by jobenass          #+#    #+#             */
/*   Updated: 2021/03/15 18:08:37 by ninieddu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_clean_lexer(t_lexer **lxr)
{
	if (!*lxr)
		return ;
	ft_strdel(&(*lxr)->line);
	ft_tabstrdel(&(*lxr)->subline);
	ft_tabstrdel(&(*lxr)->token);
	free(*lxr);
	*lxr = NULL;
}

int		ft_prepare_lexer(t_mini **shl, char *input)
{
	if (ft_check_quotes(input) == EXIT_FAILURE)
		return (256);
	if (!((*shl)->lxr = malloc(sizeof(t_lexer))))
		return (EXIT_ERROR);
	ft_bzero((*shl)->lxr, sizeof(t_lexer));
	return (EXIT_SUCCESS);
}

int		ft_is_exit_with_pipe(t_mini *shl)
{
	if (ft_strcmp(shl->lxr->token[0], "exit") == 0 && \
	(!shl->lxr->token[1] || ft_strcmp(shl->lxr->token[1], "|") != 0))
		return (1);
	return (0);
}

int		ft_lexer(t_mini *shl, char *input, int ret)
{
	int	i;

	if ((ret = ft_prepare_lexer(&shl, input)) != EXIT_SUCCESS)
		return (ret);
	shl->lxr->line = ft_get_line(input);
	if ((ret = ft_check_tokens(shl, &shl->lxr->line)) != EXIT_SUCCESS)
		return (258);
	shl->lxr->subline = ft_get_subline(shl->lxr->line);
	if (!shl->lxr->line || !shl->lxr->subline)
		ret = EXIT_ERROR;
	ft_strdel(&(shl->lxr)->line);
	i = -1;
	while (ret != EXIT_ERROR && shl->lxr->subline && shl->lxr->subline[++i])
	{
		if (!(shl->lxr->token = ft_get_token(shl->lxr->subline[i])))
			ret = EXIT_ERROR;
		if (ret != EXIT_ERROR)
			ret = ft_parser(shl, ret, 0);
		if (ft_is_exit_with_pipe(shl) == 1 || ret == 130)
			break ;
		ret = 0;
		ft_tabstrdel(&(shl->lxr)->token);
	}
	ft_clean_lexer(&shl->lxr);
	return (ret);
}
