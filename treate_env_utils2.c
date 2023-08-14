/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treate_env_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezongo <mpezongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:27:12 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/14 14:27:42 by mpezongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**treate_empty_env(void)
{
	char	**ret;

	ret = malloc(6 * 8);
	if (!ret)
		return (NULL);
	ret[0] = ft_strdup("PWD=/Users/rel-fila/Desktop/minishell");
	ret[1] = ft_strdup("SHLVL=0");
	ret[2] = ft_strdup("_=/usr/bin/env");
	ret[3] = ft_strdup("OLDPWD=""");
	ret[4] = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	ret[5] = NULL;
	return (ret);
}

t_envp	*get_var(t_envp **envp, char *str)
{
	t_envp	*tmp;

	tmp = *envp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, str, ft_strlen(str)))
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}
