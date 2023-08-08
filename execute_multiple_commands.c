#include "minishell.h"

void	close_all_fd(t_parsing *parsing, int *fd, int old)
{
	if (parsing->in_file > 2)
		close(parsing->in_file);
	if (parsing->out_file > 2)
		close(parsing->out_file);
	close(fd[1]);
	// close(fd[0]);
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

void	ft_execute_multiple_cmds(t_parsing *parsing, t_envp *env)
{
	char	**path1;
	char	*str;
	int		i;
	char	**envp;

	i = 0;
	if (parsing->words[0] == NULL)
		exit(127);
	if (parsing->out_file < 1)
		exit(1);
	path1 = ft_get_path(env);
	if (!path1 && ft_strchr(parsing->words[0], '/') == 0)
		exec_error(parsing->words[0]);
	while (path1 && path1[i])
	{
		if (ft_execute_m_cmd(&i, &str, parsing, path1) == 1)
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


void run_multiple_cmds(t_parsing *parsing, t_envp *envp)
{
    update_exit_code(envp, 0);
    if (!envp || !parsing)
        return ;
    if ((!ft_strncmp(parsing->words[0], "env", ft_strlen(parsing->words[0])) || !ft_strncmp(parsing->words[0], "export", ft_strlen(parsing->words[0])))&& !parsing->words[1])
        env_cmd(parsing, envp);
    else if (!ft_strncmp(parsing->words[0], "pwd", ft_strlen(parsing->words[0])))
        pwd_cmd(parsing, envp);
    else if (!ft_strncmp(parsing->words[0], "cd", ft_strlen(parsing->words[0])))
        cd_cmd(parsing, envp);
    else if (!ft_strncmp(parsing->words[0], "echo", ft_strlen(parsing->words[0])) && parsing->words[1])
        echo_cmd(parsing, envp);
    else if (!ft_strncmp(parsing->words[0], "export", ft_strlen(parsing->words[0])) && parsing->words[1])
        export_cmd(parsing->words, envp);
    else if (!ft_strncmp(parsing->words[0], "unset", ft_strlen(parsing->words[0])))
        unset_cmd(parsing->words, &envp);
    else if (!ft_strncmp(parsing->words[0], "exit", ft_strlen(parsing->words[0])))
        exit_cmd(parsing->words, envp);
    else
        ft_execute_multiple_cmds(parsing, envp);
    exit(0);
}

void exec_cmd(t_parsing *parsing, t_envp *envp, int *file, int pid_old)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    duplicate(parsing, file, pid_old);
    run_multiple_cmds(parsing, envp);
}


void execute_multiple_commands(t_parsing *parsing, t_envp *envp, int *file)
{
    int pid_old;
    int pid;
    int ret;

    while (parsing)
    {
        pid_old = file[0];
        if (pipe(file) == -1)
            return (ft_putstr_fd("PIPE\n", 2), exit(1));
        pid = fork();
        if (pid == -1)
            return (ft_putstr_fd("minishell: fork: Probleme in fork\n", 2));
        global.heredoc = 1;
		if (!pid)
			exec_cmd(parsing, envp, file, pid_old);
        global.heredoc = 0;
        close_all_fd(parsing, file, pid_old);
        parsing = parsing->next;
    }
	close(file[0]);
    waitpid(pid, &ret, 0);
    while (wait(NULL) != -1)
        continue ;
    get_exit_of_process(ret, envp);
}