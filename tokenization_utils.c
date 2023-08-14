/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezongo <mpezongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:26:26 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/14 13:27:04 by mpezongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_str(t_lexer *lexer, char **tmp)
{
	while (lexer)
	{
		*tmp = ft_strjoin(*tmp, lexer->str);
		free(lexer->str);
		free(lexer);
		lexer = lexer->next;
	}
	free(lexer);
}

int	check_quotes(char *data_entry)
{
	int	i;
	int	check;

	i = 0;
	while (data_entry[i])
	{
		if (data_entry[i] && (data_entry[i] == '\'' || data_entry[i] == '\"'))
		{
			check = data_entry[i];
			i++;
			while (data_entry[i] != check && data_entry[i])
				i++;
			if (data_entry[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_heredoc(char *str, int i)
{
	if (i == 0)
		return (0);
	if (!ft_strncmp(str, "<<", 2))
		return (1);
	return (0);
}
