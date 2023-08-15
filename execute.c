/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezongo <mpezongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:17:52 by rel-fila          #+#    #+#             */
/*   Updated: 2023/08/15 09:41:12 by mpezongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_dup(t_parsing *parsing, t_envp *envp, char **path, char *str)
{
	if (!parsing->words)
		exit(0);
	if (parsing->out_file < 0 || parsing->in_file < 0)
		exit(1);
	signal(SIGQUIT, SIG_DFL);
	if (parsing->out_file != 1)
		dup2(parsing->out_file, 1);
	if (parsing->in_file != 0)
		dup2(parsing->in_file, 0);
	path = ft_get_path(envp);
	if (!ft_strchr(parsing->words[0], '/') && !path)
		exec_error(parsing->words[0]);
	run_cmd(parsing, envp, path, str);
}

void	ft_execute(t_parsing *parsing, t_envp *envp)
{
	char	**path;
	char	*str;
	pid_t	id;
	int		ret;

	str = parsing->words[0];
	path = NULL;
	g_global.heredoc = 1;
	id = fork();
	if (id == 0)
		check_dup(parsing, envp, path, str);
	g_global.heredoc = 0;
	waitpid(id, &ret, 0);
	get_exit_of_process(ret, envp);
}

void	execute_one_command(t_parsing *parsing, t_envp *envp)
{
	int	len;

	len = ft_strlen(parsing->words[0]) + 1;
	update_exit_code(envp, 0);
	if (!envp || !parsing->words[0])
		return ;
	if ((!ft_strncmp(parsing->words[0], "env", len) || \
	!ft_strncmp(parsing->words[0], "export", len)) && !parsing->words[1])
		env_cmd(parsing, envp);
	else if (!ft_strncmp(parsing->words[0], "pwd", len))
		pwd_cmd(parsing, envp);
	else if (!ft_strncmp(parsing->words[0], "cd", len))
		cd_cmd(parsing, envp);
	else if (!ft_strncmp(parsing->words[0], "echo", len))
		echo_cmd(parsing, envp);
	else if (!ft_strncmp(parsing->words[0], "export", len) && parsing->words[1])
		export_cmd(parsing->words, envp);
	else if (!ft_strncmp(parsing->words[0], "unset", len))
		unset_cmd(parsing->words, &envp);
	else if (!ft_strncmp(parsing->words[0], "exit", len))
		exit_cmd(parsing->words, envp);
	else
		ft_execute(parsing, envp);
}

void	check_exit_code(t_envp *envp)
{
	if (g_global.exit_code)
	{
		while (envp)
		{
			if (!ft_strncmp(envp->name, "?", 1))
			{
				free(envp->content);
				envp->content = ft_itoa(1);
			}
			envp = envp->next;
		}
		g_global.exit_code = 0;
	}
}

void	execute(t_envp *envp, t_parsing *parsing)
{
	int	file[2];

	file[1] = -1;
	file[0] = -1;
	if (g_global.quitting)
	{
		g_global.exit_code = 1;
		update_exit_code(envp, 1);
		g_global.exit_code = 0;
		return ;
	}
	if (parsing->words[0] == NULL)
		return ;
	if (parsing->words == NULL || !ft_strlen(parsing->words[0]))
	{
		ft_putstr_fd("minishell: : No such file or directory\n", 2);
		update_exit_code(envp, 127);
	}
	else if (parsing->words[0])
	{
		if (parsing->next == NULL)
			execute_one_command(parsing, envp);
		else
			execute_multiple_commands(parsing, envp, file);
	}
}
