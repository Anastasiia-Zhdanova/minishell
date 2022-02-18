/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 22:33:57 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/13 22:34:11 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_first_pipe_inside(t_params *params, int *id_process, int **pipe)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	free(id_process);
	params->child = 1;
	close(pipe[0][0]);
}

int	ft_first_pipe(int *id_process, t_params *params, int **pipe)
{
	int	i;
	int	j;

	i = 0;
	id_process[0] = fork();
	if (id_process[0] < 0)
	{
		free(id_process);
		return (errno);
	}
	else if (id_process[0] == 0)
	{
		ft_first_pipe_inside(params, id_process, pipe);
		j = 1;
		while (j < params->count_pipes)
		{
			close(pipe[j][0]);
			close(pipe[j][1]);
			j++;
		}
		if (dup2(pipe[0][1], 1) == -1)
			return (errno);
	}
	return (0);
}

int	ft_middle_pipes_inside(t_params *params, int *id_process, int **pipe, int i)
{
	int	j;

	free(id_process);
	params->child = 1;
	close(pipe[i - 1][1]);
	j = 0;
	while (j < i - 1)
	{
		close(pipe[j][0]);
		close(pipe[j][1]);
		j++;
	}
	j = i + 1;
	while (j < params->count_pipes)
	{
		close(pipe[j][0]);
		close(pipe[j][1]);
		j++;
	}
	if (dup2(pipe[i - 1][0], 0) == -1)
		return (errno);
	close(pipe[i][0]);
	if (dup2(pipe[i][1], 1) == -1)
		return (errno);
	return (0);
}

int	ft_middle_pipes(int *id_process, t_params *params,
				int **pipe, t_list ***list_pipes)
{
	int	i;

	i = 1;
	while (i <= params->count_pipes - 1)
	{
		(*list_pipes)++;
		id_process[i] = fork();
		if (id_process[i] < 0)
		{
			free(id_process);
			return (errno);
		}
		else if (id_process[i] == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			return (ft_middle_pipes_inside(params, id_process, pipe, i));
		}
		else
			i++;
	}
	return (0);
}
