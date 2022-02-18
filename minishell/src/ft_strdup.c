/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 22:39:22 by mvirgini          #+#    #+#             */
/*   Updated: 2022/01/07 22:39:22 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *s1)
{
	char	*array;
	size_t	j;
	size_t	i;

	i = 0;
	j = ft_strlen(s1);
	array = (char *)malloc((j + 1) * sizeof(char));
	if (!array)
		return (NULL);
	while (i <= j)
	{
		array[i] = s1[i];
		i++;
	}
	return (array);
}
