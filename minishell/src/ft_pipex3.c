/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 20:26:31 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/13 20:26:31 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parser_pipex(t_list *list_str, t_list **list)
{
	int			i;
	t_list		*current_head;

	if (ft_start_vars(&i, list_str) == 258)
		return (258);
	current_head = list_str;
	while (list_str != NULL)
	{
		if (ft_strcmp(list_str->name, "|") == 0)
		{
			if (list_str->next != NULL
				&& ft_strcmp(list_str->next->name, "|") == 0)
				return (ft_err_pipex(i, list, 258));
			list[i] = ft_list_copy(current_head, list_str);
			if (!(list[i]))
				return (ft_err_pipex(i, list, 12));
			current_head = list_str->next;
			i++;
		}
		list_str = list_str->next;
	}
	list[i] = ft_list_copy(current_head, NULL);
	if (!(list[i]))
		return (ft_err_pipex(i, list, 12));
	return (0);
}

void	ft_free_pipex(t_list **list, int count_pipes)
{
	int	i;

	i = count_pipes + 1;
	while (i > 0)
	{
		ft_free_list(list[i - 1]);
		i--;
	}
	free(list);
}

void	ft_free_pipes(int **pipe, int count_pipes)
{
	while (count_pipes > 0)
	{
		free(pipe[count_pipes - 1]);
		count_pipes--;
	}
	free(pipe);
}

void	ft_close_pipes(int **pipe, int count_pipes)
{
	while (count_pipes > 0)
	{
		close(pipe[count_pipes - 1][0]);
		close(pipe[count_pipes - 1][1]);
		count_pipes--;
	}
}
