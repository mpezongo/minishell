/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezongo <mpezongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:53:15 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/14 11:53:31 by mpezongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char c)
{
	if (c == '|')
		return (1);
	if (c == '>')
		return (1);
	if (c == '<')
		return (1);
	return (0);
}

void	pass_quotes(char *args, int *i, char quote)
{
	if (args[*i] == quote)
	{
		(*i)++;
		while (args[*i] && args[*i] != quote)
			(*i)++;
		if (args[*i] == quote)
			(*i)++;
	}
}

int	set_word(char *line, int *i, t_lexer **lexer)
{
	int		start;
	t_lexer	*new;

	start = *i;
	while (line[*i] && !is_operator(line[*i]))
	{
		pass_quotes(line, i, 34);
		pass_quotes(line, i, 39);
		if (is_whitespace(line[*i]))
			break ;
		(*i)++;
	}
	new = ft_lexernew(ft_substr(line, start, *i - start), WORD);
	if (!new)
		return (1);
	ft_lexeradd_back(lexer, new);
	if (is_operator(line[*i]))
		(*i)--;
	return (0);
}

int	create_lexer_list(t_lexer **lexer, char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		by_pass_whitespace(line, &i);
		if (is_operator(line[i]))
		{
			if (set_operator(line, &i, lexer))
				return (1);
		}
		else if (line[i] != 32 && (line[i] > 13 || line[i] < 9))
		{
			if (set_word(line, &i, lexer))
				return (1);
		}
	}
	return (0);
}
