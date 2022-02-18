/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_another_commands3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:04:49 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/14 16:04:49 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_arr_to_null(char **arr)
{
	char	**header;

	if (arr != NULL)
	{
		header = arr;
		while (*arr != NULL)
		{
			free(*arr);
			arr++;
		}
		free (header);
	}
}
