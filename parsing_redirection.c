/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezongo <mpezongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:53:30 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/08 16:21:28 by mpezongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int treate_redirection_out(char *str, int check)
{
    int file;

    file = 0;
    if (str[file] == '\0')
        return (write(2, "minishell: :No such file or directory\n", 38), -1);
    if (check == 2)
        file = open(str, O_CREAT | O_RDWR | O_APPEND, 0644);
    if (check == 1)
        file = open(str, O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (file < 0)
        perror("open");
    return (file);
}

int treate_redirection_in(char *str)
{
    int file;

    file = open(str, O_RDONLY, 0644);
    if (file == -1)
        perror(str);
    return (file);
}