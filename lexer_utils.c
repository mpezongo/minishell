/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezongo <mpezongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:53:10 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/06 17:53:13 by mpezongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*ft_lexernew(char *str, int token)
{
	t_lexer		*new_element;

	new_element = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_element)
		return (0);
	new_element->str = str;
	new_element->category = token;
	new_element->banner = 0;
    new_element->next = NULL;
	return (new_element);
}

void	ft_lexeradd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
    tmp->next = new;
}

int	is_whitespace(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

void by_pass_whitespace(char *args, int *i)
{
    while ((args[*i] == ' ') || (args[*i] > 8 && args[*i] < 14))
        (*i)++;
}