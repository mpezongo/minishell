/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezongo <mpezongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 10:17:34 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/14 10:21:27 by mpezongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expand_var2(char *str, int *i, char *tmp1)
{
    char *tmp;
    char *tmp2;

    while ((str[*i] && str[*i] != ' ') && (!is_operator(str[*i])))
    {
        if (str[*i] == '$')
            tmp = expand_var(str, i, envp);
        else
        {
            tmp = get_char(str[*i]);
            (*i)++;
        }
        tmp2 = tmp1;
        free(tmp1);
        tmp1 = ft_strjoin(tmp2, tmp);
        free(tmp);
    }
    return (tmp1);
}