#include "./../minishell.h"

void pwd_cmd(t_parsing *parsing, t_envp *envp)
{
    char cwd[1024];

    if (getcwd(cwd, 1024))
    {
        ft_putstr_fd(cwd, parsing->out_file);
        ft_putstr_fd("\n", parsing->out_file);
    }
    else
    {
        while (envp)
        {
            if (!ft_strncmp(envp->name, "PWD", 3))
            {
                ft_putstr_fd(envp->content, parsing->out_file);
                ft_putstr_fd("\n", parsing->out_file);
            }
            envp = envp->next;
        }
    }
}

