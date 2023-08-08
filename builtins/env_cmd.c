#include "./../minishell.h"

void print_envp(t_envp *envp, t_parsing *parsing)
{
    while (envp)
    {
        if (envp->content && ft_strncmp(envp->name, "?", 1) && !envp->sign)
        {
            if (ft_strlen(envp->content) >= 1)
            {
                ft_putstr_fd(envp->name, parsing->out_file);
                ft_putstr_fd("=", parsing->out_file);
                ft_putstr_fd(envp->content, parsing->out_file);
                ft_putstr_fd("\n", parsing->out_file);
            }
        }
        envp = envp->next;
    }
}

void	ft_lst_clear_envp(t_envp *envp)
{
	t_envp	*head;

	while (envp != NULL)
	{
		head = envp->next;
		free(envp);
		envp = head;
	}
	envp = NULL;
}

t_envp	*ft_lst_last_envp(t_envp *lst)
{
	if (lst == NULL)
		return (0);
	while (lst)
	{
		if (lst ->next == NULL)
			return (lst);
		lst = lst ->next;
	}
	return (lst);
}

t_envp	*envp_copy(t_envp *env)
{
	t_envp	*exp;

	exp = NULL;
	while (env != NULL)
	{
		ft_lst_add_back_env(&exp, ft_lst_new_env(env->name, env->content));
		ft_lst_last_envp(exp)->sign = env->sign;
		env = env->next;
	}
	return (exp);
}

int	check_sorted(t_envp *exp)
{
	while (exp->next != NULL)
	{
		if (ft_strncmp(exp->name, exp->next->name, ft_strlen(exp->name)) > 0)
			return (0);
		exp = exp->next;
	}
	return (1);
}

void	envp_swap(t_envp **tmp)
{
	int		i;
	char	*a;

	i = 0;
	a = (*tmp)->name;
	(*tmp)->name = (*tmp)->next->name;
	(*tmp)->next->name = a;
	a = (*tmp)->content;
	(*tmp)->content = (*tmp)->next->content;
	(*tmp)->next->content = a;
	i = (*tmp)->sign;
	(*tmp)->sign = (*tmp)->next->sign;
	(*tmp)->next->sign = i;
}

t_envp *sort_envp(t_envp *envp)
{
    t_envp *tmp;
    t_envp *tmp1;

    tmp = envp_copy(envp);
    tmp1 = tmp;
    while (!check_sorted(tmp1))
    {
        tmp = tmp1;
        while (tmp->next)
        {
            if ((ft_strncmp(tmp->name, tmp->next->name, ft_strlen(tmp->name)) > 0))
                envp_swap(&tmp);
            tmp = tmp->next;
        }
    }
    return (tmp1);
}

void print_export(t_envp *envp, t_parsing *parsing)
{
    t_envp *tmp;
    t_envp *tmp1;

    tmp = NULL;
    tmp = sort_envp(envp);
    tmp1 = tmp;
    while (tmp)
    {
        if (ft_strncmp(tmp->name, "?", 1))
        {
            if (!tmp->sign && tmp->content)
            {
                ft_putstr_fd("declare -x ", parsing->out_file);
                ft_putstr_fd(tmp->name, parsing->out_file);
                if (ft_strlen(tmp->content) >= 1)
                {
                    ft_putstr_fd("=", parsing->out_file);
                    ft_putstr_fd("\"", parsing->out_file);
                    ft_putstr_fd(tmp->content, parsing->out_file);
                    ft_putstr_fd("\"", parsing->out_file);
                }
                ft_putstr_fd("\n", parsing->out_file);
            }
            else if (!tmp->sign && !tmp->content)
            {
                ft_putstr_fd("declare -x ", parsing->out_file);
                ft_putstr_fd(tmp->name, parsing->out_file);
                ft_putstr_fd("\n", parsing->out_file);
            }
        }
        tmp = tmp->next;
    }
    ft_lst_clear_envp(tmp1);
}

void env_cmd(t_parsing *parsing, t_envp *envp)
{
    if (!ft_strncmp(parsing->words[0], "env", ft_strlen(parsing->words[0])))
        print_envp(envp, parsing);
    else if (!ft_strncmp(parsing->words[0], "export", ft_strlen(parsing->words[0])))
        print_export(envp, parsing);
}