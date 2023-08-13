/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:46:20 by rel-fila          #+#    #+#             */
/*   Updated: 2023/08/13 16:39:54 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exec(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	run_cmd(t_parsing *parsing, t_envp *envp, char **path, char *str)
{
	int		i;
	char	**tmp;

	i = 0;
	while (path && path[i])
	{
		if (!ft_strchr(parsing->words[0], '/'))
			str = ft_strjoin_add_bs(path[i], parsing->words[0]);
		if (!access(str, F_OK))
			break ;
		free(str);
		str = NULL;
		i++;
	}
	if (!path && ft_strchr(parsing->words[0], '/'))
		str = ft_strdup(parsing->words[0]);
	if (!str)
		return (exec_error(parsing->words[0]));
	tmp = fill_table(envp);
	if (execve(str, parsing->words, tmp) == -1)
		return (error_exec(parsing->words[0]), exit(126));
	exit(1);
}

int	chek_word(char const *a, char c)
{
	int	i;
	int	t;

	i = 0;
	t = 0;
	while (a[i])
	{
		while (a[i] && a[i] == c)
			i++;
		if (a[i] == 0)
			break ;
		t++;
		while (a[i] && a[i] != c)
			i++;
	}
	return (t);
}

void	ft_free_all(char	**strings, int a)
{
	while (a >= 0)
	{
		free(strings[a]);
		a--;
	}
	free(strings);
	return ;
}

char	**ft_chek(char const *s, char c, char **strings, int words_count)
{
	char	*sub;
	int		index;
	int		a;
	int		l;

	index = 0;
	a = 0;
	while (a < words_count)
	{
		while (s[index] && s[index] == c)
			index++;
		l = 0;
		while (s[l + index] && s[l + index] != c)
			l++;
		sub = (char *)malloc(sizeof(char) * (l + 1));
		if (!sub)
			ft_free_all(strings, a);
		l = 0;
		while (s[index] && s[index] != c)
			sub[l++] = s[index++];
		sub[l] = 0;
		strings[a++] = sub;
	}
	strings[a] = 0;
	return (strings);
}
