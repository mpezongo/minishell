/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:27:44 by rel-fila          #+#    #+#             */
/*   Updated: 2023/08/12 18:36:45 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

t_envp	*get_envp(t_envp *envp, char *str)
{
	int	check;

	check = 0;
	while (envp != NULL)
	{
		if (!ft_strncmp(envp->name, str, ft_strlen(str)))
		{
			check = 1;
			break ;
		}
		envp = envp->next;
	}
	if (check == 0)
		return (NULL);
	return (envp);
}

int	ft_strncmp2(char *s1, char *s2, int n)
{
	if (s1 == NULL)
		return (1);
	while ((*s1 != '\0' || *s2 != '\0') && n > 0)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}

int	cd_utils(t_parsing *parsing, t_envp *envp, char *tmp)
{
	if (((parsing->words[1] && !ft_strncmp(parsing->words[1], "~", \
	ft_strlen(parsing->words[1]))) && get_envp(envp, "HOME")))
		tmp = get_envp(envp, "HOME")->content;
	else if (get_envp(envp, "OLDPWD") && \
	!ft_strncmp2(parsing->words[1], "-", ft_strlen(parsing->words[1])))
	{
		tmp = get_envp(envp, "OLDPWD")->content;
		ft_putstr_fd(tmp, parsing->out_file);
		ft_putstr_fd("\n", parsing->out_file);
	}
	if (!get_envp(envp, "HOME") && !parsing->words[1])
		ft_putstr_fd("minishell: cd: HOME not set\n", parsing->out_file);
	else if (chdir(tmp) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		update_exit_code(envp, 1);
		return (1);
	}
	return (0);
}

void	cd_utils_2(t_parsing *parsing, t_envp *envp)
{
	(void)parsing;
	if (get_envp(envp, "OLDPWD") == NULL)
	{
		ft_lst_add_back_env(&envp, ft_lst_new_env(ft_strdup("OLDPWD"), NULL));
		get_envp(envp, "OLDPWD")->sign = 1;
	}
	if (get_envp(envp, "PWD") == NULL)
	{
		ft_lst_add_back_env(&envp, ft_lst_new_env(ft_strdup("PWD"), NULL));
		get_envp(envp, "PWD")->sign = 1;
	}
}

void	cd_cmd(t_parsing *parsing, t_envp *envp)
{
	char	cwd[1024];
	char	*tmp;

	getcwd(cwd, 1024);
	tmp = parsing->words[1];
	if (cd_utils(parsing, envp, tmp))
		return ;
	cd_utils_2(parsing, envp);
	if (get_envp(envp, "OLDPWD")->content)
		free(get_envp(envp, "OLDPWD")->content);
	get_envp(envp, "OLDPWD")->content = ft_strdup(cwd);
	getcwd(cwd, 1024);
	if (get_envp(envp, "PWD")->content)
		free(get_envp(envp, "PWD")->content);
	get_envp(envp, "PWD")->content = ft_strdup(cwd);
}