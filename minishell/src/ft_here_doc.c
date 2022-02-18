/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 22:13:34 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/14 15:34:50 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parent_here_doc(int status, int *id_proc, t_params *params, int *i)
{
	waitpid(*id_proc, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
		{
			status = 1;
			printf("\n");
		}
	}
	if (status != 0)
	{
		close(params->fd_here_doc[*i - 1]);
		params->error_is_printed = 1;
		return (ft_if_error_here_doc(params, *i, status));
	}
	return (0);
}

int	ft_child_inside(t_params *params, int *i, t_list *list_commands)
{
	if (ft_child_here_doc(params, i, list_commands) == 1)
	{
		free(params->fd_here_doc);
		params->fd_here_doc = NULL;
		return (0);
	}
	return (ft_free_here_doc(params, *i));
}

int	ft_fork_here_doc(t_params *params, int *i,
			int status, t_list *list_commands)
{
	int		id_proc;

	id_proc = fork();
	if (id_proc < 0)
	{
		close(params->fd_here_doc[*i - 1]);
		return (ft_if_error_here_doc(params, *i, errno));
	}
	else if (id_proc != 0)
	{
		status = ft_parent_here_doc(status, &id_proc, params, i);
		if (status != 0)
			return (status);
		if (ft_replace_here_doc(params, i, &list_commands) == 12)
			return (12);
	}
	else
		return (ft_child_inside(params, i, list_commands));
	return (0);
}

void	ft_start_init(int *i, t_list *list_commands, t_params *params)
{
	*i = 0;
	params->fd_here_doc = NULL;
	params->name_here_doc = NULL;
	params->count_here_doc = ft_count_here_doc(list_commands);
}

int	ft_here_doc(t_list *list_commands, t_params *params)
{
	int		i;
	int		status;

	ft_start_init(&i, list_commands, params);
	if (params->count_here_doc == 0)
		return (0);
	status = ft_start_values_here_doc(params, list_commands);
	if (status != 0)
		return (status);
	while (list_commands != NULL)
	{
		if (ft_strcmp(list_commands->name, "<<") == 0)
		{
			status = ft_open_here_doc(&i, params, list_commands);
			if (status != 0)
				return (status);
			status = ft_fork_here_doc(params, &i, status, list_commands);
			if (params->child == 1 || status != 0)
				return (status);
		}
		list_commands = list_commands->next;
	}
	free(params->fd_here_doc);
	params->fd_here_doc = NULL;
	return (0);
}
