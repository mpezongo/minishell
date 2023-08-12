/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:53:20 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/12 12:11:56 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
    (void)argv;
    if (argc != 1)
        printf("This program doesn't use arguments\n");
    else
    {
        t_envp *envp;
        t_parsing *parsings;

        init_signals();
        save_env(&envp, env);
        printf("%s\n", WELCOME_MSG);
        start_shell(&envp, &parsings);
    }
    return (0);
}