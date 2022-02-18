/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 00:42:04 by mvirgini          #+#    #+#             */
/*   Updated: 2022/01/17 00:42:22 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_itoa_additional(char *count_of_digits, int n, int *i)
{
	if (n < 0)
	{
		while (n)
		{
			count_of_digits[(*i)++] = -(n % 10) + '0';
			n = n / 10;
		}
		count_of_digits[(*i)++] = '-';
	}
	else if (n > 0)
	{
		while (n)
		{
			count_of_digits[(*i)++] = (n % 10) + '0';
			n = n / 10;
		}
	}
	else
	{
		count_of_digits[(*i)++] = '0';
	}
}

char	*ft_itoa(int n)
{
	char	count_of_digits[11];
	char	*str;
	int		i;
	int		j;

	i = 0;
	ft_itoa_additional(count_of_digits, n, &i);
	str = (char *) malloc (i + 1);
	if (str == NULL)
		return (NULL);
	j = 0;
	while (i > 0)
	{
		i--;
		str[j] = count_of_digits[i];
		j++;
	}
	str[j] = '\0';
	return (str);
}
