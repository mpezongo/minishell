/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:53:20 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/15 07:58:53 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_envp		*envp;
	t_parsing	*parsings;

	(void)argv;
	if (argc != 1)
		printf("This program doesn't use arguments\n");
	else
	{
		init_signals();
		save_env(&envp, env);
		printf("%s\n", WELCOME_MSG);
		start_shell(&envp, &parsings);
	}
	return (0);
}
