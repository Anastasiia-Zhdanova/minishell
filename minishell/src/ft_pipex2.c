/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 20:22:37 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/13 20:23:31 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_pipes(t_list *list_str)
{
	int	counter;

	counter = 0;
	while (list_str != NULL)
	{
		if (ft_strcmp(list_str->name, "|") == 0)
			counter++;
		list_str = list_str->next;
	}
	return (counter);
}

int	ft_is_pipex_valid(t_list *list_head, t_list *list_last)
{
	if (ft_strcmp(list_head->name, "|") == 0
		|| ft_strcmp(list_last->name, "|") == 0)
		return (1);
	return (0);
}

void	ft_error_pipex_not_valid(t_params *params)
{
	write(2, "minishell: syntax error near unexpected token `|'\n", 50);
	params->error_is_printed = 1;
}

int	ft_err_pipex(int i, t_list **list, int status)
{
	while (i > 0)
	{
		ft_free_list(list[i - 1]);
		i--;
	}
	return (status);
}

int	ft_start_vars(int *i, t_list *list_str)
{
	*i = 0;
	if (ft_is_pipex_valid(list_str, ft_lstlast(list_str)) == 1)
		return (258);
	return (0);
}
