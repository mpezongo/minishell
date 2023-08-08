/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezongo <mpezongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:52:59 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/06 17:53:00 by mpezongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_arg(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        free(env[i]);
        i++;
    }
    free(env[i]);
}

void free_lexer(t_lexer **lst)
{
    t_lexer	*list;

	if (lst != NULL)
	{
		list = *lst;
		while (list != NULL)
		{
			if (list->category == WORD)
				free(list->str);
			free(list);
			list = list->next;
		}
		*lst = NULL;
	}
}