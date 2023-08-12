/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:53:03 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/12 12:43:05 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_heredocument_in(t_lexer *lexer, t_envp **envp)
{
    int file;
    char *name;
    char *readln;
    char *str;
    t_lexer *new;
    t_lexer *middle;
    t_lexer *node;

    file = 0;
    name = get_name_heredoc();
    file = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (file < 0)
        return (perror("open"), file);
    global.heredoc = 1;
    readln = NULL;
    str = ft_strdup(lexer->str);
    node = lexer->next;
    while (node)
    {
        if (!ft_strncmp(node->str, "cat", ft_strlen(node->str)))
        {
            if (node->next)
            {
                if (node->next->category == WORD)
                {
                    node = node->next;
                    continue ;
                }
            }
            new = ft_lexernew(ft_strdup(name), WORD);
            middle = node->next;
            node->next = new;
            new->next = middle;
            if (middle)
                middle->prev = new;
        }
        if (!ft_strncmp(node->str, "grep", ft_strlen(node->str)))
        {
            if (!node->next)
            {
                node = node->next;
                continue ;
            }
            new = ft_lexernew(ft_strdup(name), WORD);
            middle = node->next->next;
            node->next->next = new;
            new->next = middle;
            if (middle)
                middle->prev = new;
        }
        node = node->next;
    }
    if (!lexer->next || (lexer->next && lexer->next->category == PIPE))
    {
        node = lexer->prev;
        while (node)
        {
            if (node->prev)
            {
                if (!ft_strncmp(node->prev->str, "cat", ft_strlen(node->prev->str))
                    || (!ft_strncmp(node->prev->str, "grep", ft_strlen(node->prev->str)) && node->category == WORD))
                {
                    new = ft_lexernew(ft_strdup(name), WORD);
                    middle = lexer->next;
                    lexer->next = new;
                    new->next = middle;
                    if (middle)
                        middle->prev = new;
                    break ;
                }
            }
            node = node->prev;
        }
    }
    while (1)
    {
        if (open_heredoc(readln, &file, str, envp))
            break ;
    }
    close(file);
    free(str);
    if (file == -1)
        file = open(name, O_RDONLY);
    global.heredoc = 0;
    free(name);
    return (file);
}

char *get_name_heredoc(void)
{
    static int i;
    char *tmp;
    char *tmp1;

    i = 0;
    while (1)
    {
        tmp1 = ft_itoa(i);
        tmp = ft_strjoin("/tmp/", tmp1);
        free(tmp1);
        if (access(tmp, F_OK))
            break ;
        free(tmp);
        i++;
    }
    return (tmp);
}

int open_heredoc(char *readln, int *file, char *str, t_envp **envp)
{
    int index;
    char *expand;

    index = 0;
    signal(SIGINT, sigint_handler);
    readln = readline("> ");
    if (!isatty(STDIN_FILENO))
    {
        *file = -1;
        dup2(STDIN_FILENO, open(ttyname(1), O_RDONLY, 0644));
        return (1);
    }
    if ((readln == NULL || (!ft_strncmp(readln, str, ft_strlen(readln))
        && ft_strlen(readln) == ft_strlen(str))))
    {
        free(readln);
        return (1);
    }
    index = 0;
    while (readln[index])
    {
        if (readln[index] == '$')
        {
            expand = expand_var(readln, &index, envp);
            write(*file, expand, ft_strlen(expand));
            free(expand);
        }
        else
        {
            write(*file, &readln[index], 1);
            index++;
        }
    }
    write(*file, "\n", 1);
    free(readln);
    if (!global.heredoc || !readln)
		return (EXIT_FAILURE);
    return (0);
}