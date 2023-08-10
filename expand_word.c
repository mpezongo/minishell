#include "minishell.h"

int	check_variable_naming(char *value, int *a, char **tmp, int pos)
{
	if (value[*a] == '?')
		return (*tmp = ft_substr(value, pos, 1), (*a)++, 0);
	else if ((value[*a] >= 'A' && value[*a] <= 'Z') || (value[*a] >= 'a' && value[*a] <= 'z') || value[*a] == '_')
	{
		while (value[*a] && ((value[*a] >= '0' && value[*a] <= '9')
				|| (value[*a] >= 'A' && value[*a] <= 'Z')
				|| (value[*a] >= 'a' && value[*a] <= 'z')
				|| value[*a] == '_'))
		{
			(*a)++;
		}
		*tmp = ft_substr(value, pos, *a - pos);
	}
	else
		return ((*a)++, 1);
	return (0);
}

char *expand_var(char *str, int *i, t_envp **envp)
{
    t_envp *node;
    char *tmp;
    char *tmp1;
    char *tmp2;

    (*i)++;
    if (str[*i] == 0)
        return (ft_strdup("$"));
    if (check_variable_naming(str, i, &tmp, *i))
        return (ft_strdup(""));
    node = *envp;
    while (node)
    {
        if (tmp[1] == '$')
            return (tmp);
        if (!ft_strncmp(node->name, tmp, ft_strlen(node->name)))
        {
            if (node->content)
            {
                tmp1 = ft_strdup(node->content);
                if (str[*i] || ((str[*i] < '0' && str[*i] > '9')
                    && (str[*i] < 'A' || str[*i] > 'Z')
                    && (str[*i] < 'a' && str[*i] > 'z')
                    && str[*i] != '_'))
                {
                    free(tmp);
                    while ((str[*i] && str[*i] != ' ') && (!is_operator(str[*i])))
                    {
                        if (str[*i] == '$')
                            tmp = expand_var(str, i, envp);
                        else
                        {
                            tmp = get_char(str[*i]);
                            (*i)++;
                        }
                        tmp2 = tmp1;
                        free(tmp1);
                        tmp1 = ft_strjoin(tmp2, tmp);
                        free(tmp);
                    }
                    return (tmp1);
                }
                else if (str[*i] == '$')
                {
                    free(tmp);
                    tmp = expand_var(str, i, envp);
                    tmp2 = tmp1;
                    free(tmp1);
                    tmp1 = ft_strjoin(tmp2, tmp);
                    return (free(tmp), tmp1);
                }
                else
                {
                    free(tmp);
                    return (tmp1);
                }
            }
        }
        node = node->next;
    }
    free(tmp);
    return(ft_strdup(""));
}

int check_is_2_quotes(char *tmp, int quote)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (tmp[i])
    {
        if (tmp[i] == quote)
            j++;
        i++;
    }
    if (j == 2)
        return (1);
    return (0);
}

char *expand_insin_quote(char *str, int *i)
{
    char *tmp;
    int j;

    j = 0;
    (*i)++;
    while (str[*i + j] && str[*i + j] != '\'')
        j++;
    tmp = (char *)malloc(sizeof(char) * (j + 2));
    if (!tmp)
        return (NULL);
    j = 1;
    tmp[0] = '\'';
    while ((str[(*i)] && str[(*i)] != '\'') || (str[(*i) + 1] && str[(*i) + 1] != ' '))
    {
        tmp[j] = str[(*i)];
        (*i)++;
        j++;
        if (str[(*i)] == ' ' && check_is_2_quotes(tmp, '\''))
            break ;
    }
    if (!check_is_2_quotes(tmp, '\''))
    {
        tmp[j] = '\'';
        tmp[j + 1] = '\0';
    }
    else
        tmp[j] = '\0';
    return (tmp);
}

char *expand_indoub_quote(char *str, int *i, t_envp **envp)
{
    char *tmp;
    char *tmp1;
    char *tmp2;

    tmp = ft_strdup("");
    if (str[*i] == '\"' && str[*i])
    {
        tmp1 = get_char(str[*i]);
        tmp2 = tmp;
        free(tmp);
        tmp = ft_strjoin(tmp2, tmp1);
        free(tmp1);
        (*i)++;
        check_inside_for_money(str, i, &tmp, envp);
        tmp1 = get_char(str[*i]);
        tmp2 = tmp;
        free(tmp);
        tmp = ft_strjoin(tmp2, tmp1);
        free(tmp1);
        return (tmp);
    }
    return (NULL);
}

char *get_char(char c)
{
    char *tmp;
    int i;

    i = 0;
    tmp = malloc(sizeof(char) * 2);
    if (!tmp)
        return (NULL);
    tmp[0] = c;
    tmp[1] = '\0';
    return (tmp);
}

void check_inside_for_money(char *str, int *i, char **tmp, t_envp **envp)
{
    char *var;
    char *tmp1;

    while ((str[*i] != '\"' && str[*i]) || (str[(*i) + 1] && str[(*i) + 1] != ' '))
    {
        if (str[*i + 1] != '\"' && str[*i] == '$' && str[*i + 1] != ' ')
        {
            var = expand_var(str, i, envp);
            tmp1 = *tmp;
            free(*tmp);
            *tmp = ft_strjoin(tmp1, var);
        }
        else
        {
            var = get_char(str[*i]);
            tmp1 = *tmp;
            free(*tmp);
            *tmp = ft_strjoin(tmp1, var);
            (*i)++;
        }
        free(var);
        if ((str[*i] == ' ' && check_is_2_quotes(*tmp, '\'')) || !str[*i])
            break ;
    }
}