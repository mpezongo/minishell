/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezongo <mpezongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:54:07 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/06 17:54:08 by mpezongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void gather_words(t_lexer *lexer)
{
    while (lexer)
    {
        if (lexer->category == WORD)
        {
            if (ft_strchr(lexer->str, '\"') || ft_strchr(lexer->str, '\''))
            {
                lexer->str = remove_quot(lexer->str);
                lexer->banner = 1;
            }
        }
        lexer = lexer->next;
    }
}

char *remove_quot(char *str)
{
    char *tmp;
    int i;
    int j;

    i = 0;
    j = 0;
    tmp = malloc(sizeof(char) + (ft_strlen(str) + 1));
    if (!tmp)
        return (NULL);
    remove_quot_keep_track(tmp, str, &j);
    tmp[j] = 0;
    free(str);
    return (tmp);
}

void remove_quot_keep_track(char *tmp, char *str, int *j)
{
    int i;
    int check;

    i = 0;
    while (str[i])
    {
        if (str[i] && str[i] != '\"' && str[i] != '\'')
            tmp[(*j)++] = str[i++];
        if ((str[i] && str[i] == '\"') || (str[i] == '\''))
        {
            check = str[i++];
            while (str[i] != check && str[i])
                tmp[(*j)++] = str[i++];
            if (str[i] == check)
                i++;
        }
    }
}