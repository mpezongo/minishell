/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:53:20 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/07 19:03:13 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_signal(int sign)
{
    // If interrupt signal and in heredoc mode
    if (sign == 2 && global.heredoc == 1)
    {
        // Close standard input and exit heredoc mode
        close(STDIN_FILENO);
        global.heredoc = 0;
    }
    else if (sign == 2 && global.heredoc == 1)
		return ;
     // If interrupt signal and background process is running
    else if (sign == 2 && waitpid(-1, NULL, WNOHANG) !=0)
    {
        // Print newline, clear input line, and redisplay prompt
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void set_up_signals(void)
{
    // Initialize global flags
    global.heredoc = 0; // Flag for heredoc mode (not in heredoc mode initially)
    global.quitting = 0; // Flag for quitting (not quitting initially)
    // Set signal handlers for specific signals
    signal(SIGINT, handle_signal); // Set signal handler for interrupt signal (Ctrl+C)
    signal(SIGQUIT, SIG_IGN); // Ignore quit signal (Ctrl+\)
    // Disable catching of signals by readline library
    rl_catch_signals = 0;
}

int main(int argc, char **argv, char **env)
{
    (void)argv;
    if (argc != 1)
        printf("This program doesn't use arguments\n");
    else
    {
        t_envp *envp;
        t_parsing *parsings;

        //set_up_signals();
        init_signals();
        save_env(&envp, env);
        printf("%s\n", WELCOME_MSG);
        start_shell(&envp, &parsings);
    }
    return (0);
}