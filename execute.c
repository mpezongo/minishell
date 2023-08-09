#include "minishell.h"

void update_exit_code(t_envp *envp, int ret)
{
    while(envp)
    {
        if (!ft_strncmp(envp->name, "?", 1))
        {
            free(envp->content);
            envp->content = ft_itoa(ret);
        }
        envp = envp->next;
    }
}

void get_exit_of_process(int ret, t_envp *envp)
{
    int exit_code;

    exit_code = 0;
    if (WIFEXITED(ret))
        exit_code = WEXITSTATUS(ret);
    else if (WIFSIGNALED(ret))
        exit_code = WTERMSIG(ret) + 128;
    if (WTERMSIG(ret) == 2)
    {
        ft_putstr_fd("\n", 1);
        update_exit_code(envp, 130);
    }
    else if (WTERMSIG(ret) == 3)
    {
        ft_putstr_fd("Quit: 3\n", 1);
        update_exit_code(envp, 131);
    }
    while (envp)
    {
        if (!ft_strncmp(envp->name, "?", 1))
        {
            free(envp->content);
            envp->content = ft_itoa(exit_code);
        }
        envp = envp->next;
    }
}

void exec_error(char *tmp)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(tmp, 2);
    ft_putstr_fd(" ", 2);
    if (ft_strchr(tmp, '/'))
        ft_putstr_fd(": No such file or directory\n", 2);
    else
        ft_putstr_fd(": command not found\n", 2);
    exit(127);
}

char	*ft_strjoin_add_bs(char *s1, char *s2)
{
	int		a;
	int		i;
	int		l;
	char	*ptr;

	i = 0;
	l = 0;
	if (s1 == 0 || s2 == 0)
		return (0);
	a = ft_strlen(s1) + ft_strlen(s2) + 2;
	ptr = (char *)malloc(sizeof(char) * a);
	if (ptr == NULL)
		return (NULL);
	while (s1[i])
	{
		ptr[l++] = s1[i++];
	}
	ptr[l++] = '/';
	i = 0;
	while (s2[i])
	{
		ptr[l++] = s2[i++];
	}
	ptr[l] = '\0';
	return (ptr);
}

char	**fill_table(t_envp	*env)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = malloc((ft_lst_size_env(env) + 1) * sizeof(char *));
	if (!tmp)
		return (NULL);
	while (env)
	{
		tmp[i] = ft_strjoin(env->name, "=");
		tmp[i] = ft_strjoin(tmp[i], env->content);
		i++;
		env = env->next;
	}
	tmp[i] = NULL;
	return (tmp);
}

void run_cmd(t_parsing *parsing, t_envp *envp, char **path, char *str)
{
    int i;
    char **tmp;

    i = 0;
    while (path && path[i])
    {
        if (!ft_strchr(parsing->words[0], '/'))
            str = ft_strjoin_add_bs(path[i], parsing->words[0]);
        if (!access(str, F_OK))
            break ;
        free(str);
        str = NULL;
        i++;
    }
    if (!path && ft_strchr(parsing->words[0], '/'))
        str = ft_strdup(parsing->words[0]);
    if (!str)
        return (exec_error(parsing->words[0]));
    tmp = fill_table(envp);
    if (execve(str, parsing->words, tmp) == -1)
        return (perror("execve"), exit(126));
    exit(1);
}

static int	chek_word(char const *a, char c)
{
	int	i;
	int	t;

	i = 0;
	t = 0;
	while (a[i])
	{
		while (a[i] && a[i] == c)
			i++;
		if (a[i] == 0)
			break ;
		t++;
		while (a[i] && a[i] != c)
			i++;
	}
	return (t);
}

void	ft_free_all(char	**strings, int a)
{
	while (a >= 0)
	{
		free(strings[a]);
		a--;
	}
	free(strings);
	return ;
}

char	**ft_chek(char const *s, char c, char **strings, int words_count)
{
	char	*sub;
	int		index;
	int		a;
	int		l;

	index = 0;
	a = 0;
	while (a < words_count)
	{
		while (s[index] && s[index] == c)
			index++;
		l = 0;
		while (s[l + index] && s[l + index] != c)
			l++;
		sub = (char *)malloc(sizeof(char) * (l + 1));
		if (!sub)
			ft_free_all(strings, a);
		l = 0;
		while (s[index] && s[index] != c)
			sub[l++] = s[index++];
		sub[l] = 0;
		strings[a++] = sub;
	}
	strings[a] = 0;
	return (strings);
}

char	**ft_split1(char const *s, char c)
{
	char	**strings;
	int		words_count;

	if (s == 0)
		return (0);
	strings = NULL;
	words_count = chek_word(s, c);
	strings = (char **)malloc(sizeof(char *) * (words_count + 1));
	if (!strings)
		return (0);
	ft_chek(s, c, strings, words_count);
	return (strings);
}

char	**ft_get_path(t_envp *env)
{
	while (env)
	{
		if (ft_strncmp(env->name, "PATH", 4) == 0)
			return (ft_split1(env->content, ':'));
		env = env->next;
	}
	return (NULL);
}

int	ft_lst_size_env(t_envp *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst ->next;
	}
	return (count);
}

void check_dup(t_parsing *parsing, t_envp *envp, char **path, char *str)
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

void ft_execute(t_parsing *parsing, t_envp *envp)
{
    char **path;
    char *str;
    pid_t id;
    int ret;

    str = parsing->words[0];
    path = NULL;
    global.heredoc = 1;
    id = fork();
    if (id == 0)
        check_dup(parsing, envp, path, str);
    global.heredoc = 0;
    waitpid(id, &ret, 0);
    get_exit_of_process(ret, envp);
}

void execute_one_command(t_parsing *parsing, t_envp *envp)
{
    update_exit_code(envp, 0);
    if (!envp || !parsing->words[0])
        return ;
    if ((!ft_strncmp(parsing->words[0], "env", ft_strlen(parsing->words[0])) || !ft_strncmp(parsing->words[0], "export", ft_strlen(parsing->words[0])))&& !parsing->words[1])
        env_cmd(parsing, envp);
    else if (!ft_strncmp(parsing->words[0], "pwd", ft_strlen(parsing->words[0])))
        pwd_cmd(parsing, envp);
    else if (!ft_strncmp(parsing->words[0], "cd", ft_strlen(parsing->words[0])))
        cd_cmd(parsing, envp);
    else if (!ft_strncmp(parsing->words[0], "echo", ft_strlen(parsing->words[0])))
        echo_cmd(parsing, envp);
    else if (!ft_strncmp(parsing->words[0], "export", ft_strlen(parsing->words[0])) && parsing->words[1])
        export_cmd(parsing->words, envp);
    else if (!ft_strncmp(parsing->words[0], "unset", ft_strlen(parsing->words[0])))
        unset_cmd(parsing->words, &envp);
    else if (!ft_strncmp(parsing->words[0], "exit", ft_strlen(parsing->words[0])))
        exit_cmd(parsing->words, envp);
    else
        ft_execute(parsing, envp);
}

void check_exit_code(t_envp *envp)
{
    if (global.exit_code)
    {
        while(envp)
        {
            if (!ft_strncmp(envp->name, "?", 1))
            {
                free(envp->content);
                envp->content = ft_itoa(1);
            }
            envp = envp->next;
        }
        global.exit_code = 0;
    }
}

void execute(t_envp *envp, t_parsing *parsing)
{
    int file[2];

    file[1] = -1;
    file[0] = -1;
    if (global.quitting)
    {
        global.exit_code = 1;
        check_exit_code(envp);
        global.exit_code = 0;
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