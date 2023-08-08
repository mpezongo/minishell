#include "./../minishell.h"

int full_of_n(char *str)
{
    int i;

    i = 0;
    if (str == NULL)
        return (0);
    if (str[i] == '-' && str[i + 1] && str)
    {
        i++;
        while (str[i])
        {
            if (str[i] != 'n' && str[i])
                return (0);
            i++;
        }
    }
    else
        return (0);
    return (1);
}


int check_flag_for_echo(t_parsing *parsing, int *i)
{
    int check;

    check = 0;
    while (full_of_n(parsing->words[*i]))
    {
        (*i)++;
        check = 1;
    }
    return (check);
}

void echo_cmd(t_parsing *parsing, t_envp *envp)
{
    int i;
    int check;

    i = 1;
    check = 0;
    check = check_flag_for_echo(parsing, &i);
    while (parsing->words[i])
    {
        if (!ft_strncmp(parsing->words[i], "~", ft_strlen(parsing->words[i])) && parsing->words[i][0] != '\0')
        {
            ft_putstr_fd(get_envp(envp, "HOME")->content, parsing->out_file);
            i++;
        }
        else
            ft_putstr_fd(parsing->words[i++], parsing->out_file);
        if (parsing->words[i])
            ft_putstr_fd(" ", parsing->out_file);
    }
    if (check == 0)
        ft_putstr_fd("\n", parsing->out_file);
    return ;
}