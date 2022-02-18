/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 21:12:39 by mvirgini          #+#    #+#             */
/*   Updated: 2022/01/22 21:30:01 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_str_error(char *command, char *arg)
{
	char	*full_error;

	if (arg == NULL)
		full_error = command;
	else
		full_error = ft_join_for_strs(command, arg);
	if (full_error == NULL)
		return (12);
	perror(full_error);
	if (arg != NULL)
		free(full_error);
	return (errno);
}
