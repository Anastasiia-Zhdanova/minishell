/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbeata <lbeata@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:03:49 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/12 23:03:26 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	length1;
	int	length2;
	int	i;

	length1 = (int)ft_strlen(s1);
	length2 = (int)ft_strlen(s2);
	i = 0;
	while (i < length1 && i < length2 && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
