/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:28:14 by rel-fila          #+#    #+#             */
/*   Updated: 2023/08/13 14:54:55 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	check_alphabet(int a)
{
	return ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || a == '_');
}

int	check_numeric(char *input)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	while (input[i])
	{
		if (input[i] == '=')
			break ;
		if (input[i] == '-')
			return (1);
		if (input[i] == '+')
			p++;
		i++;
	}
	if (p > 1)
		return (1);
	return (0);
}

int	check(char *str, t_envp *envp)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!check_alphabet(str[0]) || check_numeric(str))
			return (1);
		while (str[i] && str[i] != '=')
		{
			if (check_alphabet(str[i]) || (str[i] >= '0' && str[i] <= '9') \
				|| (str[i] == '+' && ft_strchr(str, '=')))
				i++;
			else
			{
				update_exit_code(envp, 1);
				return (1);
			}
		}
	}
	return (0);
}

void	free_name_content(char *name, char *content)
{
	if (name)
		free(name);
	if (content)
		free(content);
}

void	pwd_cmd(t_parsing *parsing, t_envp *envp)
{
	char	cwd[1024];

	if (getcwd(cwd, 1024))
	{
		ft_putstr_fd(cwd, parsing->out_file);
		ft_putstr_fd("\n", parsing->out_file);
	}
	else
	{
		while (envp)
		{
			if (!ft_strncmp(envp->name, "PWD", 3))
			{
				ft_putstr_fd(envp->content, parsing->out_file);
				ft_putstr_fd("\n", parsing->out_file);
			}
			envp = envp->next;
		}
	}
}
