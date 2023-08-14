/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multiple_commands_utils.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:17:54 by rel-fila          #+#    #+#             */
/*   Updated: 2023/08/13 16:38:50 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_fd(t_parsing *parsing, int *fd, int old)
{
	if (parsing->in_file > 2)
		close(parsing->in_file);
	if (parsing->out_file > 2)
		close(parsing->out_file);
	close(fd[1]);
	close(old);
	if (parsing->next)
		close(fd[1]);
}

void	duplicate(t_parsing *parc, int *fd, int old)
{
	if (parc->in_file < 0 || parc->out_file < 0)
		exit(1);
	if (parc->out_file > 2)
		dup2(parc->out_file, 1);
	else if (parc->next)
	{
		dup2(fd[1], 1);
		close(fd[1]);
	}
	if (parc->in_file > 2)
		dup2(parc->in_file, 0);
	else if (old != -1)
	{
		dup2(old, 0);
		close(old);
	}
	close(old);
	close(fd[1]);
	close(fd[0]);
	if (parc->words[0] == NULL)
		exit(0);
}

int	ft_execute_m_cmd(int *i, char **str, t_parsing	*parcer, char **path1)
{
	if (ft_strchr(parcer->words[0], '/') == 0)
		*str = ft_strjoin_add_bs(path1[*i], parcer->words[0]);
	if (access(*str, F_OK) == 0)
		return (1);
	free(*str);
	*str = NULL;
	(*i)++;
	return (0);
}
