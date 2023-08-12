/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:28:14 by rel-fila          #+#    #+#             */
/*   Updated: 2023/08/10 17:28:15 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

