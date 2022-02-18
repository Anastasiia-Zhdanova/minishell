/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 20:31:00 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/14 15:24:57 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_last_pipe_parent(int *id_process, t_params *params, int **pipe, int i)
{
	ft_close_pipes(pipe, params->count_pipes);
	signal(SIGQUIT, ft_signal_quit);
	waitpid(id_process[i], &(params->status), 0);
	if (WIFEXITED(params->status))
		params->status = WEXITSTATUS(params->status);
	else if (WIFSIGNALED(params->status))
	{
		params->status = 128 + WTERMSIG(params->status);
		if (WTERMSIG(params->status) == SIGINT)
			printf("\n");
	}
	while (i > 0)
	{
		waitpid(id_process[i - 1], NULL, 0);
		i--;
	}
	signal(SIGQUIT, SIG_IGN);
	free(id_process);
	params->error_is_printed = 1;
	return (params->status);
}

int	ft_last_pipe_child(int *id_process, t_params *params, int **pipe)
{
	int	j;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	free(id_process);
	params->child = 1;
	close(pipe[params->count_pipes - 1][1]);
	j = 0;
	while (j < params->count_pipes - 1)
	{
		close(pipe[j][0]);
		close(pipe[j][1]);
		j++;
	}
	if (dup2(pipe[params->count_pipes - 1][0], 0) == -1)
		return (errno);
	return (0);
}

int	ft_last_pipe(int *id_process, t_params *params, int **pipe)
{
	int	i;

	i = params->count_pipes;
	id_process[i] = fork();
	if (id_process[i] < 0)
	{
		free(id_process);
		return (errno);
	}
	else if (id_process[i] != 0)
		return (ft_last_pipe_parent(id_process, params, pipe, i));
	else
		return (ft_last_pipe_child(id_process, params, pipe));
	return (0);
}

int	ft_fork_pipes(int **pipe, t_list **list_pipes, t_list **list_env,
			t_params *params)
{
	int	*id_process;
	int	status;

	id_process = (int *)malloc(sizeof(int) * (params->count_pipes + 1));
	if (!id_process)
		return (12);
	params->child = 0;
	status = ft_first_pipe(id_process, params, pipe);
	if (params->child == 1 && status == 0)
		return (ft_redirect(*list_pipes, params, list_env));
	else if (params->child == 1 || status != 0)
		return (status);
	status = ft_middle_pipes(id_process, params, pipe, &list_pipes);
	if (params->child == 1 && status == 0)
		return (ft_redirect(*list_pipes, params, list_env));
	else if (params->child == 1 || status != 0)
		return (status);
	list_pipes++;
	status = ft_last_pipe(id_process, params, pipe);
	if (params->child == 1 && status == 0)
		return (ft_redirect(*list_pipes, params, list_env));
	return (status);
}
