#include "./../minishell.h"

t_envp *get_envp(t_envp *envp, char *str)
{
    int check;

    check = 0;
    while (envp != NULL)
    {
        if (!ft_strncmp(envp->name, str, ft_strlen(str)))
        {
            check = 1;
            break ;
        }
        envp = envp->next;
    }
    if (check == 0)
        return (NULL);
    return (envp);
}

void cd_cmd(t_parsing *parsing, t_envp *envp)
{
    char cwd[1024];
    char *tmp;

    getcwd(cwd, 1024);
	tmp = parsing->words[1];
	if (get_envp(envp, "HOME") && ((parsing->words[1] && !ft_strncmp(parsing->words[1], "~", ft_strlen(parsing->words[1]))) || parsing->words[1] == NULL))
		tmp = get_envp(envp, "HOME")->content;
    else if (get_envp(envp, "OLDPWD") && !ft_strncmp(parsing->words[1], "-", ft_strlen(parsing->words[1])))
    {
        tmp = get_envp(envp, "OLDPWD")->content;
        ft_putstr_fd(tmp, parsing->out_file);
        ft_putstr_fd("\n", parsing->out_file);
    }
	if (chdir(tmp) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		update_exit_code(envp, 1);
		return ;
	}
    if (get_envp(envp, "OLDPWD")->content)
        free(get_envp(envp, "OLDPWD")->content);
    get_envp(envp, "OLDPWD")->content = ft_strdup(cwd);
    getcwd(cwd, 1024);
    if (get_envp(envp, "PWD")->content)
        free(get_envp(envp, "PWD")->content);
    get_envp(envp, "PWD")->content = ft_strdup(cwd);
}