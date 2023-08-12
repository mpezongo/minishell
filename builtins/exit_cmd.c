/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:27:56 by rel-fila          #+#    #+#             */
/*   Updated: 2023/08/10 17:48:08 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	check_int(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

void	exit_cmd(char **str, t_envp *envp)
{
	int		i;
	long	exit_code;

	printf("%s\n", EXIT_MSG);
	i = 1;
	if (str[i] && str[i + 1] && check_int(str[i]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str[i], 2);
		ft_putstr_fd(": too many arguments\n", 2);
		update_exit_code(envp, 1);
	}
	else if (str[i] && check_int(str[i]))
	{
		exit_code = (int)ft_atoi(str[i]);
		exit(exit_code);
	}
	else if (str[i] && !check_int(str[i]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str[i], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	exit(0);
}
