/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezongo <mpezongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:13:38 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/14 11:09:35 by mpezongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_inside_for_money(char *s, int *i, char **tmp, t_envp **envp)
{
	char	*var;
	char	*tmp1;

	while ((s[*i] != '\"' && s[*i]) || (s[(*i) + 1] && s[(*i) + 1] != ' '))
	{
		if (s[*i + 1] != '\"' && s[*i] == '$' && s[*i + 1] != ' ')
		{
			var = expand_var(s, i, envp);
			tmp1 = *tmp;
			free(*tmp);
			*tmp = ft_strjoin(tmp1, var);
		}
		else
		{
			var = get_char(s[*i]);
			tmp1 = *tmp;
			free(*tmp);
			*tmp = ft_strjoin(tmp1, var);
			(*i)++;
		}
		free(var);
		if ((s[*i] == ' ' && check_is_2_quotes(*tmp, '\'')) || !s[*i])
			break ;
	}
}

char	*expand_indoub_quote(char *str, int *i, t_envp **envp)
{
	char	*tmp;
	char	*tmp1;
	char	*tmp2;

	tmp = ft_strdup("");
	if (str[*i] == '\"' && str[*i])
	{
		tmp1 = get_char(str[*i]);
		tmp2 = tmp;
		free(tmp);
		tmp = ft_strjoin(tmp2, tmp1);
		free(tmp1);
		(*i)++;
		check_inside_for_money(str, i, &tmp, envp);
		tmp1 = get_char(str[*i]);
		tmp2 = tmp;
		free(tmp);
		tmp = ft_strjoin(tmp2, tmp1);
		free(tmp1);
		return (tmp);
	}
	return (NULL);
}

char	*expand_insin_quote(char *str, int *i)
{
	char	*tmp;
	int		j;

	j = 0;
	(*i)++;
	while (str[*i + j] && str[*i + j] != '\'')
		j++;
	tmp = (char *)malloc(sizeof(char) * (j + 2));
	if (!tmp)
		return (NULL);
	j = 1;
	tmp[0] = '\'';
	while ((str[(*i)] && str[(*i)] != '\'')
		|| (str[(*i) + 1] && str[(*i) + 1] != ' '))
	{
		tmp[j] = str[(*i)];
		(*i)++;
		j++;
		if (str[(*i)] == ' ' && check_is_2_quotes(tmp, '\''))
			break ;
	}
	return (expand_insin_quote2(tmp, j));
}

char	*expand_insin_quote2(char *tmp, int j)
{
	if (!check_is_2_quotes(tmp, '\''))
	{
		tmp[j] = '\'';
		tmp[j + 1] = '\0';
	}
	else
		tmp[j] = '\0';
	return (tmp);
}
