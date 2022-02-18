/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:20:19 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/11 18:29:13 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_fill_list_redir(t_list *list, t_list **list_redirects)
{
	t_list	*lst_tmp;

	while (list != NULL)
	{
		if (ft_strcmp(list->name, "<") != 0
			&& ft_strcmp(list->name, ">") != 0
			&& ft_strcmp(list->name, ">>") != 0)
		{
			lst_tmp = ft_create_element(list->name, NULL);
			if (!lst_tmp)
			{
				ft_free_list(*list_redirects);
				return (12);
			}
			ft_push_back(list_redirects, lst_tmp);
		}
		else
			list = list->next;
		list = list->next;
	}
	return (0);
}

static int	ft_full_redir_two(t_redirect *redir, t_list *list_commands,
								int i, t_params *params)
{
	int	status;

	if (ft_strcmp(list_commands->name, ">>") == 0)
	{
		redir->fd[i] = open(list_commands->next->name, O_RDWR | O_APPEND
				| O_CREAT, S_IRWXU | S_IRWXO | S_IRWXG);
		status = ft_check_fd_second(redir, list_commands, params, i);
		if (status != 0)
			return (status);
	}
	return (0);
}

static int	ft_open_fd_redir(t_redirect *redir, t_list *list_commands,
							int i, t_params *params)
{
	int	status;

	if (ft_strcmp(list_commands->name, "<") == 0)
	{
		redir->fd[i] = open(list_commands->next->name, O_RDONLY);
		status = ft_check_fd(redir, list_commands, params, i);
		if (status != 0)
			return (status);
	}
	if (ft_strcmp(list_commands->name, ">") == 0)
	{
		redir->fd[i] = open(list_commands->next->name, O_RDWR
				| O_TRUNC | O_CREAT, S_IRWXU | S_IRWXO | S_IRWXG);
		status = ft_check_fd_second(redir, list_commands, params, i);
		if (status != 0)
			return (status);
	}
	status = ft_full_redir_two(redir, list_commands, i, params);
	if (status != 0)
		return (status);
	return (0);
}

int	ft_open_files(t_redirect *redir, t_list *list_commands,
					t_list **list_redirects, t_params *params)
{
	int		i;
	int		status;
	t_list	*head;

	head = list_commands;
	i = 0;
	redir->fd = (int *)malloc(sizeof(int) * redir->count);
	if (!redir)
		return (12);
	while (list_commands != NULL)
	{
		status = ft_open_fd_redir(redir, list_commands, i, params);
		if (status != 0)
			return (status);
		i++;
		list_commands = list_commands->next;
	}
	status = ft_fill_list_redir(head, list_redirects);
	if (status != 0)
	{
		ft_close_fd(redir);
		free(redir->fd);
		return (status);
	}
	return (0);
}
