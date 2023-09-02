/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treate2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezongo <mpezongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:12:19 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/14 14:13:44 by mpezongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*treate_dou_quote(char *str, int *i, char *tmp, t_envp **envp)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = get_char(str[*i]);
	tmp2 = tmp;
	free(tmp);
	tmp = ft_strjoin(tmp2, tmp1);
	free(tmp1);
	(*i)++;
	while (str[*i] && str[*i] != '\"')
	{
		if (str[*i] == '$')
			treate_quote2(str, &tmp, envp, i);
		else
		{
			tmp1 = get_char(str[*i]);
			tmp2 = tmp;
			free(tmp);
			tmp = ft_strjoin(tmp2, tmp1);
			free(tmp1);
			(*i)++;
		}
	}
	return (tmp);
}

char	*treate_sin_quote(char *str, int *i, char *tmp)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = get_char(str[*i]);
	tmp2 = tmp;
	free(tmp);
	tmp = ft_strjoin(tmp2, tmp1);
	free(tmp1);
	(*i)++;
	while (str[*i] && str[*i] != '\'')
	{
		tmp1 = get_char(str[*i]);
		tmp2 = tmp;
		free(tmp);
		tmp = ft_strjoin(tmp2, tmp1);
		free(tmp1);
		(*i)++;
	}
	return (tmp);
}

void	treate_quote2(char *str, char **tmp, t_envp **envp, int *i)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = expand_var(str, i, envp);
	tmp2 = *tmp;
	free(*tmp);
	*tmp = ft_strjoin(tmp2, tmp1);
	free(tmp1);
}
