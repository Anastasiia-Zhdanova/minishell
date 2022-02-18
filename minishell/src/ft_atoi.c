/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 21:54:51 by mvirgini          #+#    #+#             */
/*   Updated: 2022/01/22 22:40:11 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdigit(int c)
{
	if ((c >= 48 && c <= 57))
		return (1);
	else
		return (0);
}

static int	ft_isspace(char simbol)
{
	if ((simbol == ' ') || (simbol == '\f') || (simbol == '\n')
		|| (simbol == '\r') || (simbol == '\t') || (simbol == '\v'))
	{
		return (1);
	}
	return (0);
}

static int	ft_is_plus_minus(char **str)
{
	if ((**str == '-') && (**str != 0))
	{
		(*str)++;
		return (-1);
	}
	else if ((**str == '+') && (**str != 0))
	{
		(*str)++;
		return (1);
	}
	return (1);
}

int	ft_atoi(char *str)
{
	int					i;
	unsigned long long	number_result;

	while ((*str != 0) && (ft_isspace(*str) == 1))
	{
		str++;
	}
	i = ft_is_plus_minus(&str);
	number_result = 0;
	while (ft_isdigit(*str))
	{
		if (((number_result == 922337203685477580) && (*str - '0') > 6)
			|| (number_result > 922337203685477580))
		{
			if (i == 1)
				return (-1);
			if (i == -1)
				return (0);
		}
		number_result = (*str - '0') + number_result * 10;
		str++;
	}
	return ((int)(i * number_result));
}
