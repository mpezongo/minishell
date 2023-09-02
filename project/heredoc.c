/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezongo <mpezongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:53:03 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/14 14:52:37 by mpezongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_heredocument_in(t_lexer *lexer, t_envp **envp)
{
	int		file;
	char	*name;
	char	*readln;
	char	*str;

	file = 0;
	name = get_name_heredoc();
	file = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (file < 0)
		return (perror("open"), file);
	g_global.heredoc = 1;
	readln = NULL;
	str = ft_strdup(lexer->str);
	while (1)
	{
		if (open_heredoc(readln, &file, str, envp))
			break ;
	}
	close(file);
	free(str);
	if (file != -1)
		file = open(name, O_RDONLY);
	g_global.heredoc = 0;
	free(name);
	return (file);
}

char	*get_name_heredoc(void)
{
	static int	i;
	char		*tmp;
	char		*tmp1;

	i = 0;
	while (1)
	{
		tmp1 = ft_itoa(i);
		tmp = ft_strjoin("/tmp/", tmp1);
		free(tmp1);
		if (access(tmp, F_OK))
			break ;
		free(tmp);
		i++;
	}
	return (tmp);
}

int	open_heredoc(char *readln, int *file, char *str, t_envp **envp)
{
	signal(SIGINT, sigint_handler);
	readln = readline("> ");
	if (!isatty(STDIN_FILENO))
	{
		*file = -1;
		dup2(STDIN_FILENO, open(ttyname(1), O_RDONLY, 0644));
		return (1);
	}
	if ((readln == NULL || (!ft_strncmp(readln, str, ft_strlen(readln))
				&& ft_strlen(readln) == ft_strlen(str))))
	{
		free(readln);
		return (1);
	}
	open_heredoc2(readln, file, envp);
	free(readln);
	if (!g_global.heredoc || !readln)
		return (EXIT_FAILURE);
	return (0);
}

void	open_heredoc2(char *readln, int *file, t_envp **envp)
{
	int		index;
	char	*expand;

	index = 0;
	while (readln[index])
	{
		if (readln[index] == '$')
		{
			expand = expand_var(readln, &index, envp);
			write(*file, expand, ft_strlen(expand));
			free(expand);
		}
		else
		{
			write(*file, &readln[index], 1);
			index++;
		}
	}
	write(*file, "\n", 1);
}
