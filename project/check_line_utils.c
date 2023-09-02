/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezongo <mpezongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:52:29 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/12 18:15:15 by mpezongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '|')
			i++;
		while (line[i] && (line[i] == 32 || (line[i] < 13 && line[i] > 9)))
			i++;
		if (line[i] == '|')
			return (1);
	}
	return (0);
}
