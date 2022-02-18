/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 15:26:21 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/10 18:56:47 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_list *list_args)
{
	if (list_args == NULL)
		return ;
	else if (ft_strcmp(list_args->name, "-n") == 0)
	{
		list_args = list_args->next;
		while (list_args != NULL)
		{
			if (list_args->next != NULL)
				printf("%s ", list_args->name);
			else
				printf("%s", list_args->name);
			list_args = list_args->next;
		}
	}
	else
	{
		while (list_args != NULL)
		{
			if (list_args->next != NULL)
				printf("%s ", list_args->name);
			else
				printf("%s\n", list_args->name);
			list_args = list_args->next;
		}
	}
}
