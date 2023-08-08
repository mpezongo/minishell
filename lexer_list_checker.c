/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list_checker.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezongo <mpezongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:53:05 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/06 17:53:06 by mpezongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_lexer_list_redirec(int category)
{
    if (category == RIN)
        return (printf("minshell: syntax error near unexpected token `<'\n"), 1);
    if (category == ROUT)
        return (printf("minshell: syntax error near unexpected token `>'\n"), 1);
    if (category == APPEND)
        return (printf("minshell: syntax error near unexpected token `>>'\n"), 1);
    if (category == HEREDOCUMENT)
        return (printf("minshell: syntax error near unexpected token `<<'\n"), 1);
    if (category == PIPE)
        return (printf("minshell: syntax error near unexpected token `|'\n"), 1);
    return (0);
}

int check_lexer_list(t_lexer *lexer)
{
    int i;
    t_lexer *tmp;
    i = 0;
    tmp = lexer;
    
    if (tmp->category == PIPE)
        return (printf("minshell: syntax error near unexpected token `|'\n"), 1);
    while (tmp)
    {
        if (tmp->category == PIPE)
        {
            if (tmp->next && tmp->next->category == PIPE)
                return (printf("PIPE errors\n"), 1);
        }
        else if (tmp->category != WORD && tmp->next)
        {
            if (check_lexer_list_redirec(tmp->next->category))
                return (1);
        }
        i++;
        if (tmp->category != WORD && i == ft_lstsize(lexer))
            return (printf("minishell: syntax error near unexpected token `newline'\n"), 1);
        tmp = tmp->next;
    }
    return (0);
}