/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multiple_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:17:27 by rel-fila          #+#    #+#             */
/*   Updated: 2023/08/15 09:21:05 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	catch_exit(t_parsing *parsing)
{
	if (parsing->words[0] == NULL)
		exit (127);
	if (parsing->out_file < 1)
		exit (1);
}

void	ft_execute_multiple_cmds(t_parsing *parsing, t_envp *env)
{
	char	**path;
	char	*str;
	int		i;
	char	**envp;

	i = 0;
	catch_exit(parsing);
	path = ft_get_path(env);
	if (!path && ft_strchr(parsing->words[0], '/') == 0)
		exec_error(parsing->words[0]);
	while (path && path[i])
	{
		if (ft_execute_m_cmd(&i, &str, parsing, path) == 1)
			break ;
	}
	if (ft_strchr(parsing->words[0], '/') != 0)
		str = ft_strdup(parsing->words[0]);
	if (str == NULL)
		return (exec_error(parsing->words[0]), exit(127));
	envp = fill_table(env);
	if (execve(str, parsing->words, envp) == -1)
		return (perror("execve"), exit(126));
	exit(1);
}

void	run_multiple_cmds(t_parsing *parsing, t_envp *envp)
{
	int	len;

	len = ft_strlen(parsing->words[0]);
	update_exit_code(envp, 0);
	if (!envp || !parsing)
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
		ft_execute_multiple_cmds(parsing, envp);
	exit(0);
}

void	exec_cmd(t_parsing *parsing, t_envp *envp, int *file, int pid_old)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	duplicate(parsing, file, pid_old);
	run_multiple_cmds(parsing, envp);
}

void	execute_multiple_commands(t_parsing *parsing, t_envp *envp, int *file)
{
	int	pid_old;
	int	pid;
	int	ret;

	while (parsing)
	{
		pid_old = file[0];
		if (pipe(file) == -1)
			return (ft_putstr_fd("PIPE\n", 2), exit(1));
		pid = fork();
		if (pid == -1)
			return (ft_putstr_fd("minishell: fork: Probleme in fork\n", 2));
		g_global.heredoc = 1;
		if (!pid)
			exec_cmd(parsing, envp, file, pid_old);
		g_global.heredoc = 0;
		close_all_fd(parsing, file, pid_old);
		parsing = parsing->next;
	}
	close(file[0]);
	waitpid(pid, &ret, 0);
	while (wait(NULL) != -1)
		continue ;
	get_exit_of_process(ret, envp);
}
