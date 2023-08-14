/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezongo <mpezongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:54:16 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/14 13:27:00 by mpezongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenization(char *data_entry, char **tmp, t_envp **envp)
{
	int		i;
	char	**str;

	i = 0;
	data_entry = divide_words(data_entry);
	if (check_quotes(data_entry))
		return (free(data_entry), 1);
	invert_inside_quotes(data_entry);
	tmp = ft_split(data_entry, ' ');
	str = tmp;
	while (str[i])
		invert_inside_quotes(str[i++]);
	i = 0;
	while (str[i])
	{
		if (!check_heredoc(str[i - 1], i))
			str[i] = expand_word(str[i], *envp);
		i++;
	}
	free(data_entry);
	return (0);
}

char	*divide_words(char *data_entry)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
	i = 0;
	str = malloc(ft_strlen(data_entry) * 2);
	if (!str)
		return (NULL);
	while (data_entry[i])
	{
		add_spaces(&i, &j, str, data_entry);
		i++;
	}
	str[j] = 0;
	return (str);
}

void	add_spaces(int *i, int *j, char *str, char *data_entry)
{
	int	check;

	if (data_entry[*i] && (data_entry[*i] == '\'' || data_entry[*i] == '\"'))
	{
		check = data_entry[*i];
		str[(*j)++] = data_entry[(*i)++];
		while (data_entry[*i] != check && data_entry[*i])
			str[(*j)++] = data_entry[(*i)++];
		str[(*j)++] = data_entry[*i];
	}
	else if ((data_entry[*i] == '|' || data_entry[*i] == '>'
			|| data_entry[*i] == '<') && data_entry[*i])
	{
		str[(*j)++] = ' ';
		if (data_entry[*i] == data_entry[(*i) + 1])
			str[(*j)++] = data_entry[(*i)++];
		str[(*j)++] = data_entry[*i];
		str[(*j)++] = ' ';
	}
	else
		str[(*j)++] = data_entry[*i];
}

char	*expand_word(char *str, t_envp *envp)
{
	int		i;
	t_lexer	*lexer;
	char	*tmp;

	i = 0;
	tmp = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
			ft_lexeradd_back(&lexer,
				ft_lexernew(expand_var(str, &i, &envp), WORD));
		if (str[i] == '\'')
			ft_lexeradd_back(&lexer,
				ft_lexernew(expand_insin_quote(str, &i), WORD));
		if (str[i] == '\"')
			ft_lexeradd_back(&lexer,
				ft_lexernew(expand_indoub_quote(str, &i, &envp), WORD));
		if (str[i] && str[i] != '\"' && str[i] != '\'' && str[i] != '$')
		{
			ft_lexeradd_back(&lexer, ft_lexernew(get_char(str[i]), WORD));
			i++;
		}
	}
	get_str(lexer, &tmp);
	return (free(str), tmp);
}
