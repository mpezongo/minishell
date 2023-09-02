/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treate_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezongo <mpezongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:25:52 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/15 09:51:11 by mpezongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_env(t_envp **envp, int check, char **env)
{
	int		i;
	t_envp	*node;

	i = 0;
	node = *envp;
	if (check > 0)
	{
		while (node)
		{
			if (!ft_strncmp(node->name, "PATH", 4)
				|| !ft_strncmp(node->name, "OLDPWD", 6))
				node->sign = 1;
			node = node->next;
		}
		free_arg(env);
	}
	while (node)
	{
		if (!ft_strncmp(node->name, "OLDPWD", ft_strlen(node->name)))
			node->sign = 1;
		node = node->next;
	}
	ft_lst_add_front_env(envp, ft_lst_new_env(ft_strdup("?"), ft_strdup("0")));
	if (get_var(envp, "OLDPWD") == NULL)
		ft_lst_add_back_env(envp, ft_lst_new_env(ft_strdup("OLDPWD"), NULL));
}

void	increment_shell_level(char **content)
{
	int	value;

	value = ft_atoi(*content);
	if (*content == 0)
		*content = ft_strdup("1");
	else if (value == 999)
	{
		free(*content);
		(*content) = ft_strdup("");
	}
	else if (value < 0)
	{
		free(*content);
		*content = ft_strdup("0");
	}
	else
	{
		free(*content);
		*content = ft_itoa(value + 1);
	}
}

char	*get_env_name(char *env)
{
	int		i;
	char	*str;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	str = malloc(sizeof(char *) * i);
	if (!str)
		return (0);
	i = 0;
	while (env[i] && env[i] != '=')
	{
		str[i] = env[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_env_content(char *env)
{
	int		i;
	char	*content;
	int		j;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	content = malloc(sizeof(char *) * (ft_strlen(env) - i + 1));
	if (!content)
		return (0);
	j = -1;
	while (env[++i])
		content[++j] = env[i];
	return (content);
}

void	save_env(t_envp **envp, char **env)
{
	int		i;
	char	*name;
	char	*content;
	t_envp	*tmp;
	int		check;

	check = 0;
	i = -1;
	if (!env[0])
	{
		check = 1;
		env = treate_empty_env();
	}
	while (env[++i])
	{
		name = get_env_name(env[i]);
		content = get_env_content(env[i]);
		if (!ft_strncmp(name, "SHLVL", ft_strlen(name)))
			increment_shell_level(&content);
		tmp = ft_lst_new_env(name, content);
		ft_lst_add_back_env(envp, tmp);
	}
	ft_check_env(envp, check, env);
}
