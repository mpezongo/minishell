/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezongo <mpezongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:52:59 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/14 12:09:03 by mpezongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_operator(char *line, int *i, t_lexer **lexer_list)
{
	t_lexer	*new;

	new = NULL;
	if (line[*i] == '>')
	{
		if (treate_sup(line, i, lexer_list, new))
			return (1);
	}
	else if (line[*i] == '<')
	{
		if (treate_inf(line, i, lexer_list, new))
			return (1);
	}
	else
	{
		new = ft_lexernew("|", PIPE);
		if (!new)
			return (1);
		ft_lexeradd_back(lexer_list, new);
	}
	return (0);
}

int	treate_sup(char *line, int *i, t_lexer **lexer_list, t_lexer *new)
{
	if (line[*i + 1] == '>')
	{
		(*i)++;
		new = ft_lexernew(">>", APPEND);
		if (!new)
			return (1);
		ft_lexeradd_back(lexer_list, new);
	}
	else
	{
		new = ft_lexernew(">", ROUT);
		if (!new)
			return (1);
		ft_lexeradd_back(lexer_list, new);
	}
	return (0);
}

int	treate_inf(char *line, int *i, t_lexer **lexer_list, t_lexer *new)
{
	if (line[*i + 1] == '<')
	{
		(*i)++;
		new = ft_lexernew("<<", HEREDOCUMENT);
		if (!new)
			return (1);
		ft_lexeradd_back(lexer_list, new);
	}
	else
	{
		new = ft_lexernew("<", RIN);
		if (!new)
			return (1);
		ft_lexeradd_back(lexer_list, new);
	}
	return (0);
}
