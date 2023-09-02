/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezongo <mpezongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:04:00 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/14 11:38:05 by mpezongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_variable_naming(char *value, int *a, char **tmp, int pos)
{
	if (value[*a] == '?')
		return (*tmp = ft_substr(value, pos, 1), (*a)++, 0);
	else if ((value[*a] >= 'A' && value[*a] <= 'Z') || (value[*a] >= 'a'
			&& value[*a] <= 'z') || value[*a] == '_')
	{
		while (value[*a] && ((value[*a] >= '0' && value[*a] <= '9')
				|| (value[*a] >= 'A' && value[*a] <= 'Z')
				|| (value[*a] >= 'a' && value[*a] <= 'z')
				|| value[*a] == '_'))
			(*a)++;
		*tmp = ft_substr(value, pos, *a - pos);
	}
	else
		return ((*a)++, 1);
	return (0);
}

char	*expand_var(char *str, int *i, t_envp **envp)
{
	t_envp	*node;
	char	*tmp;

	(*i)++;
	if (str[*i] == 0)
		return (ft_strdup("$"));
	if (check_variable_naming(str, i, &tmp, *i))
		return (ft_strdup(""));
	node = *envp;
	while (node)
	{
		if (tmp[1] == '$')
			return (tmp);
		if (!ft_strncmp(node->name, tmp, ft_strlen(node->name)))
		{
			if (node->content)
				return (free(tmp), expard_var3(str, i, envp, node));
		}
		node = node->next;
	}
	free(tmp);
	return (ft_strdup(""));
}

int	check_is_2_quotes(char *tmp, int quote)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tmp[i])
	{
		if (tmp[i] == quote)
			j++;
		i++;
	}
	if (j == 2)
		return (1);
	return (0);
}

char	*get_char(char c)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char) * 2);
	if (!tmp)
		return (NULL);
	tmp[0] = c;
	tmp[1] = '\0';
	return (tmp);
}
