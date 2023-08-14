/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:27:53 by rel-fila          #+#    #+#             */
/*   Updated: 2023/08/13 15:01:11 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	envp_swap(t_envp **tmp)
{
	int		i;
	char	*a;

	i = 0;
	a = (*tmp)->name;
	(*tmp)->name = (*tmp)->next->name;
	(*tmp)->next->name = a;
	a = (*tmp)->content;
	(*tmp)->content = (*tmp)->next->content;
	(*tmp)->next->content = a;
	i = (*tmp)->sign;
	(*tmp)->sign = (*tmp)->next->sign;
	(*tmp)->next->sign = i;
}

t_envp	*sort_envp(t_envp *envp)
{
	t_envp	*tmp;
	t_envp	*tmp1;

	tmp = envp_copy(envp);
	tmp1 = tmp;
	while (!check_sorted(tmp1))
	{
		tmp = tmp1;
		while (tmp->next)
		{
			if ((ft_strncmp(tmp->name, tmp->next->name, \
							ft_strlen(tmp->name)) > 0))
				envp_swap(&tmp);
			tmp = tmp->next;
		}
	}
	return (tmp1);
}

void	print_print(t_parsing *parsing, t_envp *tmp)
{
	ft_putstr_fd("declare -x ", parsing->out_file);
	ft_putstr_fd(tmp->name, parsing->out_file);
	if (ft_strlen(tmp->content) >= 1)
	{
		ft_putstr_fd("=", parsing->out_file);
		ft_putstr_fd("\"", parsing->out_file);
		ft_putstr_fd(tmp->content, parsing->out_file);
		ft_putstr_fd("\"", parsing->out_file);
	}
	ft_putstr_fd("\n", parsing->out_file);
}

void	print_export(t_envp *envp, t_parsing *parsing)
{
	t_envp	*tmp;
	t_envp	*tmp1;

	tmp = NULL;
	tmp = sort_envp(envp);
	tmp1 = tmp;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "?", 1))
		{
			if (!tmp->sign && tmp->content)
			{
				print_print(parsing, tmp);
			}
			else if (!tmp->sign && !tmp->content)
			{
				ft_putstr_fd("declare -x ", parsing->out_file);
				ft_putstr_fd(tmp->name, parsing->out_file);
				ft_putstr_fd("\n", parsing->out_file);
			}
		}
		tmp = tmp->next;
	}
	ft_lst_clear_envp(tmp1);
}

void	env_cmd(t_parsing *parsing, t_envp *envp)
{
	if (!ft_strncmp(parsing->words[0], "env", ft_strlen(parsing->words[0])))
		print_envp(envp, parsing);
	else if (!ft_strncmp(parsing->words[0], "export", \
				ft_strlen(parsing->words[0])))
		print_export(envp, parsing);
}
