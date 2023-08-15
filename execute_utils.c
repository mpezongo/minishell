/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:39:51 by rel-fila          #+#    #+#             */
/*   Updated: 2023/08/14 18:25:36 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_exit_code(t_envp *envp, int ret)
{
	while (envp)
	{
		if (!ft_strncmp(envp->name, "?", 1))
		{
			free(envp->content);
			envp->content = ft_itoa(ret);
		}
		envp = envp->next;
	}
}

void	get_exit_of_process(int ret, t_envp *envp)
{
	int	exit_code;

	exit_code = 0;
	if (WIFEXITED(ret))
		exit_code = WEXITSTATUS(ret);
	else if (WIFSIGNALED(ret))
		exit_code = WTERMSIG(ret) + 128;
	if (WTERMSIG(ret) == 2)
	{
		ft_putstr_fd("\n", 1);
		update_exit_code(envp, 130);
		exit_code = 130;
	}
	else if (WTERMSIG(ret) == 3)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		update_exit_code(envp, 131);
		exit_code = 131;
	}
	update_exit_code(envp, exit_code);
}

void	exec_error(char *tmp)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(tmp, 2);
	ft_putstr_fd(" ", 2);
	if (ft_strchr(tmp, '/'))
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

char	*ft_strjoin_add_bs(char *s1, char *s2)
{
	int		a;
	int		i;
	int		l;
	char	*ptr;

	i = 0;
	l = 0;
	if (s1 == 0 || s2 == 0)
		return (0);
	a = ft_strlen(s1) + ft_strlen(s2) + 2;
	ptr = (char *)malloc(sizeof(char) * a);
	if (ptr == NULL)
		return (NULL);
	while (s1[i])
	{
		ptr[l++] = s1[i++];
	}
	ptr[l++] = '/';
	i = 0;
	while (s2[i])
	{
		ptr[l++] = s2[i++];
	}
	ptr[l] = '\0';
	return (ptr);
}

char	**fill_table(t_envp	*env)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = malloc((ft_lst_size_env(env) + 1) * sizeof(char *));
	if (!tmp)
		return (NULL);
	while (env)
	{
		tmp[i] = ft_strjoin(env->name, "=");
		tmp[i] = ft_strjoin(tmp[i], env->content);
		i++;
		env = env->next;
	}
	tmp[i] = NULL;
	return (tmp);
}
