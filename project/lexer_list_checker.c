/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list_checker.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezongo <mpezongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:53:05 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/14 12:54:23 by mpezongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print(int i)
{
	if (i == 6)
		printf("minishell: syntax error near unexpected token `newline'\n");
	else if (i == 1)
		printf("minshell: syntax error near unexpected token `<'\n");
	else if (i == 2)
		printf("minshell: syntax error near unexpected token `>'\n");
	else if (i == 3)
		printf("minshell: syntax error near unexpected token `>>'\n");
	else if (i == 4)
		printf("minshell: syntax error near unexpected token `<<'\n");
	else if (i == 5)
		printf("minshell: syntax error near unexpected token `|'\n");
}

int	check_lexer_list_redirec(int category)
{
	if (category == RIN)
		return (print(1), 1);
	if (category == ROUT)
		return (print(2), 1);
	if (category == APPEND)
		return (print(3), 1);
	if (category == HEREDOCUMENT)
		return (print(4), 1);
	if (category == PIPE)
		return (print(5), 1);
	return (0);
}

int	check_lexer_list(t_lexer *lexer)
{
	int		i;
	t_lexer	*tmp;

	i = 0;
	tmp = lexer;
	if (tmp->category == PIPE)
		return (print(5), 1);
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
			return (print(6), 1);
		tmp = tmp->next;
	}
	return (0);
}
