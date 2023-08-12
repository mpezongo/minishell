/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezongo <mpezongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:52:36 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/12 18:06:51 by mpezongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	invert_inside_quotes(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\"')
		{
			i++;
			while (line[i] && line[i] != '\"')
			{
				line[i] = line[i] * -1;
				i++;
			}
		}
		if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
			{
				line[i] = line[i] * -1;
				i++;
			}
		}
	}
}

int	check_quotes(char *line)
{
	int	i;
	int	d;
	int	s;

	i = -1;
	d = 0;
	s = 0;
	while (line[++i])
	{
		if (line[i] == '\"')
			d++;
		if (line[i] == '\'')
			s++;
	}
	if ((d && d % 2 != 0) || (s && s % 2 != 0))
		return (1);
	return (0);
}

int	check_line(char *line)
{
	int	check;

	check = 0;
	invert_inside_quotes(line);
	if (check_quotes(line))
		return (1);
	invert_inside_quotes(line);
	return (0);
}
