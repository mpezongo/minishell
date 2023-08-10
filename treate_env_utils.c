/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treate_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:54:19 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/10 16:44:24 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp *ft_lst_new_env(char *name, char *content)
{
    t_envp *tmp;

    tmp = (t_envp *)malloc(sizeof(t_envp));
    if (!tmp)
        return (0);
    tmp->name = name;
    tmp->content = content;
    tmp->next = NULL;
    tmp->sign = 0;
    return (tmp);
}

void ft_lst_add_back_env(t_envp **lst, t_envp *new)
{
    t_envp *list;

    if (*lst == NULL)
        *lst = new;
    else
    {
        list = ft_lstlast(*(lst));
        list->next = new;
    }
}

void	ft_lst_add_front_env(t_envp **lst, t_envp *new)
{
	if (!lst || !new)
		return ;
	new -> next = *lst;
	*lst = new;
}

t_envp *ft_lstlast(t_envp *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst)
	{
        if (lst ->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

char **treate_empty_env(void)
{
     char **ret;

    ret = malloc(6 * 8);
    if (!ret)
        return (NULL);
    ret[0] = ft_strdup("PWD=/Users/rel-fila/Desktop/minishell");
    ret[1] = ft_strdup("SHLVL=0");
    ret[2] = ft_strdup("_=/usr/bin/env");
    ret[3] = ft_strdup("OLDPWD=""");
    ret[4] = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
    ret[5] = NULL;
    return (ret);
}

t_envp *get_var(t_envp **envp, char *str)
{
    t_envp *tmp;

    tmp = *envp;
    while (tmp)
    {
        if (!ft_strncmp(tmp->name, str, ft_strlen(str)))
            break ;
        tmp = tmp->next;
    }
    return (tmp);
}