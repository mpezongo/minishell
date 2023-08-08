/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:53:37 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/08 21:20:30 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parser_2(t_lexer **lexer, int *in_file, int *out_file, t_envp **envp)
{
    if ((*lexer)->category == ROUT)
        *out_file = treate_redirection_out((*lexer)->next->str, 1);
    else if ((*lexer)->category == RIN)
        *in_file = treate_redirection_in((*lexer)->next->str);
    else if ((*lexer)->category == HEREDOCUMENT)
        *in_file = get_heredocument_in((*lexer)->next, envp);
    else if ((*lexer)->category == APPEND)
        *out_file = treate_redirection_out((*lexer)->next->str, 2);
    else
        return (0);
    (*lexer) = (*lexer)->next;
    return (0);
}

char **get_parc(int *in_file, int *out_file, t_lexer **lexer, t_envp **envp)
{
    char **tmp;
    int i;

    i = 0;
    *in_file = 0;
    *out_file = 1;
    tmp = malloc((count_words(*lexer) + 2) * sizeof(char *));
    while (*lexer && (*lexer)->category != PIPE)
    {
        if ((*lexer)->category == WORD)
            parser_1(*lexer, &i, tmp);
        else
            parser_2(lexer, in_file, out_file, envp);
        *lexer = (*lexer)->next;
    }
    tmp[i] = NULL;
    return (tmp);
}

void parser_1(t_lexer *lexer, int *i, char **tmp)
{
    int index;
    char **tmp1;

    if (lexer->banner == 0)
    {
        index = 0;
        tmp1 = ft_split(lexer->str, ' ');
        while (tmp1 && tmp1[index] != NULL)
            tmp[(*i)++] = tmp1[index++];
        free(tmp1);
    }
    else
        tmp[(*i)++] = ft_strdup(lexer->str);
}

int parsing(t_lexer **lexer, t_parsing **parsing, t_envp **envp)
{
     int out_file;
    int in_file;
    char **tmp;
    t_lexer *node;

    node = *lexer;
    while (node != NULL)
    {
        tmp = get_parc(&in_file, &out_file, &node, envp);
        ft_lst_add_back_parser(parsing, ft_lst_new_parser(in_file, out_file, tmp));
        if (node)
            node = node->next;
    }
    return (0);
}