/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezongo <mpezongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:54:10 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/14 14:52:37 by mpezongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	if (sig == 2 && g_global.heredoc == 1)
	{
		close(STDIN_FILENO);
		g_global.heredoc = 0;
	}
	else if (sig == 2 && g_global.heredoc == 0 && waitpid(-1, NULL, WNOHANG) != 0)
	{
		g_global.exit_code = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signals(void)
{
	g_global.quitting = 0;
	g_global.heredoc = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;
}
