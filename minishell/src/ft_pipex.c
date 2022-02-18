/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbeata <lbeata@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:41:47 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/13 20:31:27 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipex_process_inside(t_params *params, int **pipes)
{
	int	i;

	i = 0;
	while (i < params->count_pipes)
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			ft_free_pipes(pipes, i);
			return (12);
		}
		i++;
	}
	i = 0;
	while (i < params->count_pipes)
	{
		if (pipe(pipes[i]) == -1)
		{
			ft_close_pipes(pipes, i);
			ft_free_pipes(pipes, params->count_pipes);
			return (errno);
		}
		i++;
	}
	return (0);
}

int	ft_pipex_process(t_list **list_pipes, t_list **list_env, t_params *params)
{
	int	**pipes;
	int	status;

	pipes = (int **)malloc(sizeof(int *) * (params->count_pipes));
	if (!pipes)
		return (12);
	status = ft_pipex_process_inside(params, pipes);
	if (status != 0)
		return (status);
	status = ft_fork_pipes(pipes, list_pipes, list_env, params);
	if (status != 0)
	{
		ft_close_pipes(pipes, params->count_pipes);
		ft_free_pipes(pipes, params->count_pipes);
		return (status);
	}
	ft_close_pipes(pipes, params->count_pipes);
	ft_free_pipes(pipes, params->count_pipes);
	return (0);
}

int	ft_pipex(t_list *list_str, t_list **list_env, t_params *params)
{
	t_list		**list;
	int			status;

	list = (t_list **)malloc(sizeof(t_list *) * (params->count_pipes + 1));
	if (!list)
		return (12);
	status = ft_parser_pipex(list_str, list);
	if (status != 0)
	{
		if (status == 258)
			ft_error_pipex_not_valid(params);
		free (list);
		return (status);
	}
	status = ft_pipex_process(list, list_env, params);
	if (status != 0)
	{
		ft_free_pipex(list, params->count_pipes);
		return (status);
	}
	ft_free_pipex(list, params->count_pipes);
	return (0);
}
