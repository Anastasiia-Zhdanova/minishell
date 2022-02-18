/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbeata <lbeata@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 10:23:18 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/14 15:52:56 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_more_then_zero(t_redirect *redir, t_list *list_commands,
					t_list **list_redirects, t_params *params)
{
	int	status;

	if (redir->count > 0)
	{
		status = ft_redir_is_valid(list_commands, params);
		if (status > 0)
		{
			if (*list_redirects != list_commands)
				ft_free_list(*list_redirects);
			free(redir);
			return (status);
		}
		status = ft_open_files(redir, list_commands, list_redirects, params);
		if (status > 0)
		{
			if (*list_redirects != list_commands)
				ft_free_list(*list_redirects);
			free(redir);
			return (status);
		}
	}
	return (0);
}

static int	ft_parent_process(int id_proc, t_redirect *redir,
				t_list *list_commands, t_list *list_redirects)
{
	int	status;

	signal(SIGQUIT, ft_signal_quit);
	waitpid(id_proc, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			printf("\n");
	}
	signal(SIGQUIT, SIG_IGN);
	if (list_redirects != list_commands)
		ft_free_list(list_redirects);
	free(redir);
	return (status);
}

static int	ft_start_values_redir(int *status, t_list *list_commands,
				t_list **list_redirects, t_redirect **redir)
{
	*status = 0;
	*list_redirects = NULL;
	*redir = (t_redirect *)malloc(sizeof(t_redirect));
	if (!(*redir))
		return (12);
	(*redir)->count = ft_count_redirects(list_commands);
	if ((*redir)->count == 0)
		*list_redirects = list_commands;
	return (0);
}

static int	ft_fork_redir(t_list *list_commands, t_params *params,
				t_redirect *redir, t_list	*list_redirects)
{
	int	id_proc;

	id_proc = fork();
	if (id_proc < 0)
	{
		if (list_redirects != list_commands)
			ft_free_list(list_redirects);
		free(redir);
		return (errno);
	}
	else if (id_proc == 0)
	{
		params->child = 1;
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else
	{
		params->error_is_printed = 1;
		return (ft_parent_process(id_proc, redir,
				list_commands, list_redirects));
	}
	return (0);
}

int	ft_redirect(t_list *list_commands, t_params *params, t_list **list_env)
{
	int			status;
	t_redirect	*redir;
	t_list		*list_redirects;

	if (ft_start_values_redir(&status, list_commands,
			&list_redirects, &redir) == 12)
		return (12);
	else if (params->count_pipes == 0 && redir->count != 0)
	{
		status = ft_fork_redir(list_commands, params, redir, list_redirects);
		if (params->child != 1)
			return (status);
	}
	status = ft_count_more_then_zero(redir, list_commands,
			&list_redirects, params);
	if (status != 0)
		return (status);
	status = ft_execute_command(list_redirects, list_env, params);
	if (redir->count > 0)
		ft_close_fd(redir);
	if (list_redirects != list_commands)
		ft_free_list(list_redirects);
	free(redir);
	return (status);
}
