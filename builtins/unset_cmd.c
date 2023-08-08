#include "./../minishell.h"

void unset_error(char *str, t_envp *envp)
{
    ft_putstr_fd("minishell: unset: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
    update_exit_code(envp, 1);
}

void	unset_clear_node(t_envp **h)
{
	if (((*h)->name))
		free((*h)->name);
	if (((*h)->content))
		free((*h)->content);
	free((*h));
}

void	unset_helper(t_envp *head, t_envp *head0, t_envp **env)
{
	if (head == *env)
	{
		head = (*env)->next;
		unset_clear_node(env);
		*env = head;
	}
	else
	{
		while (head0->next != NULL && head != *env)
		{
			if (head0->next == head)
			{
				head0->next = head->next;
				unset_clear_node(&head);
				break ;
			}
			head0 = head0->next;
		}
	}
}

int check_equal(char *str)
{
	int i;

	i = 0;
	printf("%s\n", str);
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	unset_cmd(char **str, t_envp **envp)
{
	int		i;
	t_envp	*head;
	t_envp	*head0;

	i = 1;
	head = *envp;
	head0 = *envp;
	while (str && str[i])
	{
		head0 = *envp;
		if (check(str[i], *envp) || check_existed(*envp, str[i]) || (ft_strchr(str[i], '=') && ft_strlen(str[i]) == 1))
		{
			if (check(str[i], *envp)
				|| (ft_strchr(str[i], '=') && ft_strlen(str[i]) == 1))
				unset_error(str[i], *envp);
			i++;
			continue ;
		}
		head = get_envp(*envp, str[i]);
		unset_helper(head, head0, envp);
		i++;
	}
}