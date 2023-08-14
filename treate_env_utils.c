/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treate_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezongo <mpezongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:25:39 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/14 14:27:38 by mpezongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*ft_lst_new_env(char *name, char *content)
{
	t_envp	*tmp;

	tmp = (t_envp *)malloc(sizeof(t_envp));
	if (!tmp)
		return (0);
	tmp->name = name;
	tmp->content = content;
	tmp->next = NULL;
	tmp->sign = 0;
	return (tmp);
}

void	ft_lst_add_back_env(t_envp **lst, t_envp *new)
{
	t_envp	*list;

	if (*lst == NULL)
		*lst = new;
	else
	{
		list = ft_lstlast(*(lst));
		list->next = new;
	}
}

void	ft_lst_add_front_env(t_envp **lst, t_envp *new)
{
	if (!lst || !new)
		return ;
	new -> next = *lst;
	*lst = new;
}

t_envp	*ft_lstlast(t_envp *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
