/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezongo <mpezongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:52:55 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/12 18:30:18 by mpezongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*divide_words(char *line)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
	i = 0;
	str = malloc(ft_strlen(line) * 2);
	if (!str)
		return (NULL);
	while (line[i])
	{
		add_spaces(&i, &j, str, line);
		i++;
	}
	str[j] = 0;
	return (str);
}

void	add_spaces(int *i, int *j, char *str, char *line)
{
	int	c;

	if (line[*i] && (line[*i] == '\'' || line[*i] == '\"'))
	{
		c = line[*i];
		str[(*j)++] = line[(*i)++];
		while (line[*i] && line[*i] != c)
			str[(*j)++] = line[(*i)++];
		str[(*j)++] = line[(*i)];
	}
	else if (line[*i] && (line[*i] == '|'
			|| line[*i] == '>' || line[*i] == '<'))
	{
		str[(*j)++] = ' ';
		if (line[*i] == line[(*i) + 1])
			str[(*j)++] = line[(*i)++];
		str[(*j)++] = line[*i];
		str[(*j)++] = ' ';
	}
	else
		str[(*j)++] = line[*i];
}

int	check_heredoc(char *str, int i)
{
	if (i == 0)
		return (0);
	if (!ft_strncmp(str, "<<", 2))
		return (1);
	return (0);
}

t_lexer	*expand(char *line, t_envp **envp)
{
	int		i;
	char	*str;
	t_lexer	*lexer;

	i = 0;
	str = divide_words(line);
	lexer = NULL;
	while (str[i])
	{
		if (str[i] == '$')
			treate_dollar(lexer, envp, str, &i);
		else if (str[i] == '\'')
			ft_lexeradd_back(&lexer,
				ft_lexernew(expand_insin_quote(str, &i), WORD));
		else if (str[i] == '\"')
			ft_lexeradd_back(&lexer,
				ft_lexernew(expand_indoub_quote(str, &i, envp), WORD));
		else if (is_operator(str[i]))
			treate_operator(str, &lexer, &i);
		else
			treate_word(str, &lexer, &i, envp);
		if (str[i])
			i++;
	}
	return (free(str), lexer);
}
