/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:33:03 by rel-fila          #+#    #+#             */
/*   Updated: 2023/08/06 16:33:05 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	ft_end(const char *set, const char *s1)
{
	size_t	len;
	int		j;
	int		k;

	len = ft_strlen(s1);
	while (len)
	{
		j = 0;
		k = 0;
		while (set[j] != '\0')
		{
			if (set[j] == s1[len - 1])
			{
				k = 1;
				break ;
			}
			j++;
		}
		if (k == 1)
			len--;
		else
			break ;
	}
	return (len);
}

static size_t	ft_start(const char *set, const char *s1)
{
	size_t	len;
	int		k;
	int		j;

	len = 0;
	while (s1[len] != '\0')
	{
		j = 0;
		k = 0;
		while (set[j] != '\0')
		{
			if (set[j] == s1[len])
			{
				k = 1;
				break ;
			}
			j++;
		}
		if (k == 1)
			len++;
		else
			break ;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	start;
	size_t	end;

	if (set == NULL)
		return ((char *)s1);
	if (s1 == NULL)
		return (NULL);
	start = ft_start(set, s1);
	end = ft_end(set, s1);
	if (end > start)
	{
		str = malloc(sizeof(char) * (end - start + 1));
		if (str == NULL)
			return (NULL);
		ft_strlcpy(str, s1 + start, end - start + 1);
		return (str);
	}
	else
		return (ft_strdup(""));
}
