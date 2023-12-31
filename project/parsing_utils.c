/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezongo <mpezongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:53:33 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/14 13:04:48 by mpezongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_count_words(char *str, int *word_count)
{
	int	i;

	i = 0;
	(*word_count)++;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			while (str[i] && (str[i] == ' ' || str[i] == '\t'))
				i++;
			if (str[i] != '\0')
				(*word_count)++;
		}
		i++;
	}
}

t_parsing	*ft_lst_new_parser(int in_file, int out_file, char **str)
{
	t_parsing	*head;

	head = (t_parsing *)malloc(sizeof(t_parsing));
	if (!head)
		return (NULL);
	head->words = str;
	head->in_file = in_file;
	head->out_file = out_file;
	head->next = NULL;
	return (head);
}

t_parsing	*ft_lst_last_parsing(t_parsing *lst)
{
	if (lst == NULL)
		return (0);
	while (lst)
	{
		if (lst ->next == NULL)
			return (lst);
		lst = lst ->next;
	}
	return (lst);
}

void	ft_lst_add_back_parser(t_parsing **lst, t_parsing *new)
{
	t_parsing	*t;

	if (*lst)
	{
		t = ft_lst_last_parsing(*lst);
		t ->next = new;
	}
	else
		*lst = new;
}
