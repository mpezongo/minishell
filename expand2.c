/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezongo <mpezongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:16:11 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/13 15:13:13 by mpezongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	treate_dollar(t_lexer *lexer, t_envp **envp, char *str, int *i)
{
	char	*tmp;
	char	**strs;
	int		j;

	tmp = expand_var(str, i, envp);
	strs = ft_split(tmp, ' ');
	j = 0;
	if (strs[0])
	{
		while (strs && strs[j])
		{
			ft_lexeradd_back(&lexer, ft_lexernew(strs[j], WORD));
			j++;
		}
		free(strs);
		free(tmp);
	}
	else
	{
		ft_lexeradd_back(&lexer, ft_lexernew(tmp, WORD));
		free(strs);
	}
	(*i)--;
}
