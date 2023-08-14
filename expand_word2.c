/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezongo <mpezongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 10:17:34 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/14 10:58:44 by mpezongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_var2(char *str, int *i, char *tmp1, t_envp **envp)
{
	char	*tmp;
	char	*tmp2;

	while ((str[*i] && str[*i] != ' ') && (!is_operator(str[*i])))
	{
		if (str[*i] == '$')
			tmp = expand_var(str, i, envp);
		else
		{
			tmp = get_char(str[*i]);
			(*i)++;
		}
		tmp2 = tmp1;
		free(tmp1);
		tmp1 = ft_strjoin(tmp2, tmp);
		free(tmp);
	}
	return (tmp1);
}

char	*expard_var3(char *str, int *i, t_envp **envp, t_envp *node)
{
	char	*tmp;
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strdup(node->content);
	tmp = NULL;
	if (str[*i] || ((str[*i] < '0' && str[*i] > '9')
			&& (str[*i] < 'A' || str[*i] > 'Z')
			&& (str[*i] < 'a' && str[*i] > 'z') && str[*i] != '_'))
		return (expand_var2(str, i, tmp1, envp));
	else if (str[*i] == '$')
	{
		free(tmp);
		tmp = expand_var(str, i, envp);
		tmp2 = tmp1;
		free(tmp1);
		tmp1 = ft_strjoin(tmp2, tmp);
		return (free(tmp), tmp1);
	}
	free(tmp);
	return (tmp1);
}
