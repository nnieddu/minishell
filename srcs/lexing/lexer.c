////////////////////////////////////////////////////////////////////////////////
//
// 		███    ██  ██████  ████████ ███████ ███████ 
// 		████   ██ ██    ██    ██    ██      ██      
// 		██ ██  ██ ██    ██    ██    █████   ███████ 
// 		██  ██ ██ ██    ██    ██    ██           ██ 
// 		██   ████  ██████     ██    ███████ ███████ 
//
////////////////////////////////////////////////////////////////////////////////

#include "../../incs/minishell.h"

void		ft_clean_lexer(t_lexer **lxr)
{
	if (!*lxr)
		return ;
	ft_strdel(&(*lxr)->line);
	ft_tabstrdel(&(*lxr)->subline);
	ft_tabstrdel(&(*lxr)->token);
	free(*lxr);
	*lxr = NULL;
}

static int	ft_prepare_lexer(t_mini **shl, char *input)
{
	(void)input; // ft_check_syntax
	// if (ft_check_syntax(input) == EXIT_FAILURE)
	//	return (EXIT_FAILURE);
	if (!((*shl)->lxr = malloc(sizeof(t_lexer))))
		return (EXIT_FAILURE);
	ft_bzero((*shl)->lxr, sizeof(t_lexer));
	return (EXIT_SUCCESS);
}

int			ft_lexer(t_mini *shl, char *input, int ret)
{
	int		i;

	if (ft_prepare_lexer(&shl, input) == EXIT_FAILURE)
		return(EXIT_FAILURE);
	shl->lxr->line = ft_get_line(input);
	ft_strdel(&input);
	shl->lxr->subline = ft_get_subline(shl->lxr->line);
	if (!shl->lxr->line || !shl->lxr->subline)
		return(EXIT_FAILURE);
	ft_strdel(&(shl->lxr)->line);
	ret = EXIT_SUCCESS;
	i = -1;
	while (shl->lxr->subline && shl->lxr->subline[++i] && ret != EXIT_FAILURE)
	{
		if (!(shl->lxr->token = ft_get_token(shl->lxr->subline[i])))
			ret = EXIT_FAILURE;
		if (ret != EXIT_FAILURE)
			ret = ft_parser(shl, ret);
		ft_tabstrdel(&(shl->lxr)->token);
	}
	ft_clean_lexer(&shl->lxr);
	return (ret);
}