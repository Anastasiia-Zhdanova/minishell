/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbeata <lbeata@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 01:42:32 by lbeata            #+#    #+#             */
/*   Updated: 2022/02/12 23:03:27 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char simb)
{
	char	*arr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!(s1))
		return (NULL);
	arr = (char *)malloc(ft_strlen(s1) + 1 + 1);
	if (!(arr))
		return (NULL);
	while (s1[i] != '\0')
	{
		arr[i] = s1[i];
		i++;
	}
	arr[i + j] = simb;
	j++;
	arr[i + j] = '\0';
	return (arr);
}

char	*ft_join_for_strs(char *s1, char *s2)
{
	char	*arr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!(s1 && s2))
		return (NULL);
	arr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!(arr))
		return (NULL);
	while (s1[i] != '\0')
	{
		arr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		arr[i + j] = s2[j];
		j++;
	}
	arr[i + j] = '\0';
	return (arr);
}

int	ft_strchr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
	}
	if (s[i] == c)
	{
		return (i);
	}
	return (-1);
}

char	*ft_strjoin_path(char *s1, char *s2)
{
	char	*arr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!(s1 && s2))
		return (NULL);
	arr = (char *)malloc((ft_strchr(s1, 0)
				+ ft_strchr(s2, 0) + 2) * sizeof(char));
	if (!(arr))
		return (NULL);
	while (s1[j] != '\0')
	{
		arr[i++] = s1[j++];
	}
	arr[i++] = '/';
	j = 0;
	while (s2[j] != '\0')
	{
		arr[i++] = s2[j++];
	}
	arr[i] = '\0';
	return (arr);
}
