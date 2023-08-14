/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:05:38 by rel-fila          #+#    #+#             */
/*   Updated: 2023/08/13 16:35:58 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	print_envp(t_envp *envp, t_parsing *parsing)
{
	while (envp)
	{
		if (envp->content && ft_strncmp(envp->name, "?", 1) && !envp->sign)
		{
			if (ft_strlen(envp->content) >= 1)
			{
				ft_putstr_fd(envp->name, parsing->out_file);
				ft_putstr_fd("=", parsing->out_file);
				ft_putstr_fd(envp->content, parsing->out_file);
				ft_putstr_fd("\n", parsing->out_file);
			}
		}
		envp = envp->next;
	}
}

void	ft_lst_clear_envp(t_envp *envp)
{
	t_envp	*head;

	while (envp != NULL)
	{
		head = envp->next;
		free(envp);
		envp = head;
	}
	envp = NULL;
}

t_envp	*ft_lst_last_envp(t_envp *lst)
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

t_envp	*envp_copy(t_envp *env)
{
	t_envp	*exp;

	exp = NULL;
	while (env != NULL)
	{
		ft_lst_add_back_env(&exp, ft_lst_new_env(env->name, env->content));
		ft_lst_last_envp(exp)->sign = env->sign;
		env = env->next;
	}
	return (exp);
}

int	check_sorted(t_envp *exp)
{
	while (exp->next != NULL)
	{
		if (ft_strncmp(exp->name, exp->next->name, ft_strlen(exp->name)) > 0)
			return (0);
		exp = exp->next;
	}
	return (1);
}
