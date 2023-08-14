/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:49:19 by rel-fila          #+#    #+#             */
/*   Updated: 2023/08/13 15:49:49 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split1(char const *s, char c)
{
	char	**strings;
	int		words_count;

	if (s == 0)
		return (0);
	strings = NULL;
	words_count = chek_word(s, c);
	strings = (char **)malloc(sizeof(char *) * (words_count + 1));
	if (!strings)
		return (0);
	ft_chek(s, c, strings, words_count);
	return (strings);
}

char	**ft_get_path(t_envp *env)
{
	while (env)
	{
		if (ft_strncmp(env->name, "PATH", 4) == 0)
			return (ft_split1(env->content, ':'));
		env = env->next;
	}
	return (NULL);
}

int	ft_lst_size_env(t_envp *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst ->next;
	}
	return (count);
}
