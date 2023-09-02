/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezongo <mpezongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:54:25 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/14 14:13:31 by mpezongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	treate_operator(char *str, t_lexer **lexer, int *i)
{
	if (str[*i] == '>')
	{
		if (str[(*i) + 1] == '>')
		{
			ft_lexeradd_back(lexer, ft_lexernew(">>", APPEND));
			(*i)++;
		}
		else
			ft_lexeradd_back(lexer, ft_lexernew(">", ROUT));
	}
	else if (str[*i] == '<')
	{
		if (str[(*i) + 1] == '<')
		{
			ft_lexeradd_back(lexer, ft_lexernew("<<", HEREDOCUMENT));
			(*i)++;
		}
		else
			ft_lexeradd_back(lexer, ft_lexernew("<", RIN));
	}
	else
		ft_lexeradd_back(lexer, ft_lexernew("|", PIPE));
}

void	treate_word(char *str, t_lexer **lexer, int *i, t_envp **envp)
{
	char	*tmp;

	if (str[*i] != ' ')
	{
		tmp = ft_strdup("");
		while (str[*i] && str[*i] != ' ')
		{
			if (str[*i] == '\"')
				tmp = treate_dou_quote(str, i, tmp, envp);
			else if (str[*i] == '\'')
				tmp = treate_sin_quote(str, i, tmp);
			if (str[*i])
				treate_word2(str, &tmp, i, envp);
		}
		ft_lexeradd_back(lexer, ft_lexernew(tmp, WORD));
	}
}

void	treate_word2(char *str, char **tmp, int *i, t_envp **envp)
{
	char	*tmp1;
	char	*tmp2;

	if (str[*i] == '$')
	{
		tmp1 = expand_var(str, i, envp);
		tmp2 = *tmp;
		free(*tmp);
		*tmp = ft_strjoin(tmp2, tmp1);
		free(tmp1);
	}
	tmp1 = get_char(str[*i]);
	tmp2 = *tmp;
	free(*tmp);
	*tmp = ft_strjoin(tmp2, tmp1);
	free(tmp1);
	if (str[*i])
		(*i)++;
}
