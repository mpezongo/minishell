/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:28:12 by rel-fila          #+#    #+#             */
/*   Updated: 2023/08/13 16:35:37 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	export_error(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	add_non_existed_node(char **name, char **content, t_envp *envp)
{
	if (ft_strchr(*name, '+'))
		(*name)[ft_strlen(*name) - 1] = '\0';
	ft_lst_add_back_env(&envp, ft_lst_new_env(*name, *content));
}

char	*ft_strjoin_content(char *s1, char *s2)
{
	int		i;
	int		l;
	char	*ptr;

	i = 0;
	l = 0;
	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	ptr = (char *)malloc(1 * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (ptr == NULL)
		return (NULL);
	while (s1[i])
		ptr[l++] = s1[i++];
	i = 0;
	while (s2[i])
		ptr[l++] = s2[i++];
	ptr[l] = '\0';
	free(s1);
	return (ptr);
}

void	add_existed_node(char *name, char *content, t_envp *envp)
{
	t_envp	*head;

	head = envp;
	if (ft_strchr(name, '+') == 0)
	{
		head = get_envp(envp, name);
		free(name);
		free(head->content);
		head->content = content;
	}
	else if (ft_strchr(name, '+'))
	{
		while (head != NULL)
		{
			if (!ft_strncmp(head->name, name, ft_strlen(name) - 1))
				break ;
			head = head->next;
		}
		free(name);
		head->content = ft_strjoin_content(head->content, content);
		free(content);
	}
}

void	export_cmd(char **str, t_envp *envp)
{
	int		i;
	char	*name;
	char	*content;

	i = 1;
	while (str[i])
	{
		name = get_env_name(str[i]);
		content = get_env_content(str[i]);
		if (!ft_strlen(name) || check(str[i], envp))
		{
			free_name_content(name, content);
			export_error(str[i]);
			i++;
			continue ;
		}
		if (check_existed(envp, name))
			add_non_existed_node(&name, &content, envp);
		else if (!check_existed(envp, name) && content)
			add_existed_node(name, content, envp);
		else if (!check_existed(envp, name) && !content)
			free(name);
		i++;
	}
}
