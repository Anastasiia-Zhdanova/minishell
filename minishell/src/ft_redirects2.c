/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:07:57 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/11 16:14:22 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_redirects(t_list *list_commands)
{
	int	count;

	count = 0;
	while (list_commands != NULL)
	{
		if (ft_strcmp(list_commands->name, "<") == 0
			|| ft_strcmp(list_commands->name, ">") == 0
			|| ft_strcmp(list_commands->name, ">>") == 0)
			count++;
		list_commands = list_commands->next;
	}
	return (count);
}

int	ft_redir_is_valid(t_list *list_commands, t_params *params)
{
	int	status;

	while (list_commands != NULL)
	{
		if (ft_strcmp(list_commands->name, "<") == 0
			|| ft_strcmp(list_commands->name, ">") == 0
			|| ft_strcmp(list_commands->name, ">>") == 0)
		{
			status = ft_check_redir(list_commands, params);
			if (status != 0)
				return (status);
		}
		list_commands = list_commands->next;
	}
	return (0);
}

int	ft_check_fd_second(t_redirect *redir, t_list *list_commands,
						t_params *params, int i)
{
	if (redir->fd[i] < 0)
	{
		ft_str_error("minishell: ", list_commands->next->name);
		params->error_is_printed = 1;
		while (i > 0)
		{
			close(redir->fd[i - 1]);
			i--;
		}
		free(redir->fd);
		return (errno);
	}
	if (dup2(redir->fd[i], 1) == -1)
	{
		ft_str_error("minishell: ", list_commands->next->name);
		params->error_is_printed = 1;
		while (i >= 0)
		{
			close(redir->fd[i]);
			i--;
		}
		free(redir->fd);
		return (errno);
	}
	return (0);
}

int	ft_check_fd(t_redirect *redir, t_list *list_commands,
				t_params *params, int i)
{
	if (redir->fd[i] < 0)
	{
		ft_str_error("minishell: ", list_commands->next->name);
		params->error_is_printed = 1;
		while (i > 0)
		{
			close(redir->fd[i - 1]);
			i--;
		}
		free(redir->fd);
		return (errno);
	}
	if (dup2(redir->fd[i], 0) == -1)
	{
		ft_str_error("minishell: ", list_commands->next->name);
		params->error_is_printed = 1;
		while (i >= 0)
		{
			close(redir->fd[i]);
			i--;
		}
		free(redir->fd);
		return (errno);
	}
	return (0);
}

void	ft_close_fd(t_redirect *redir)
{
	while (redir->count > 0)
	{
		close(redir->fd[redir->count - 1]);
		redir->count--;
	}
}
