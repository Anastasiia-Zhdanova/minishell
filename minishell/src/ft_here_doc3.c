/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:18:26 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/13 18:25:50 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_free_here_doc(t_params *params, int i)
{
	close(params->fd_here_doc[i - 1]);
	free(params->fd_here_doc);
	params->fd_here_doc = NULL;
	while (i > 0)
	{
		free(params->name_here_doc[i - 1]);
		i--;
	}
	free(params->name_here_doc);
	params->name_here_doc = NULL;
	return (0);
}

int	ft_replace_here_doc(t_params *params, int *i, t_list **list_commands)
{
	char	*str;

	close(params->fd_here_doc[*i - 1]);
	str = ft_strdup("<");
	if (!str)
		return (ft_if_error_here_doc(params, *i, 12));
	free((*list_commands)->name);
	free((*list_commands)->next->name);
	(*list_commands)->name = str;
	(*list_commands)->next->name = ft_strdup(params->name_here_doc[*i - 1]);
	if (!((*list_commands)->next->name))
		return (ft_if_error_here_doc(params, *i, 12));
	*list_commands = (*list_commands)->next;
	return (0);
}

int	ft_child_here_doc(t_params *params, int *i, t_list *list_commands)
{
	char	*str;

	params->child = 1;
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		tcsetattr(0, TCSANOW, &params->consol_ignore);
		str = readline("> ");
		tcsetattr(0, TCSANOW, &params->start_consol);
		if (!str)
			return (1);
		if (ft_strcmp(list_commands->next->name, str) == 0)
		{
			free(str);
			return (1);
		}
		write(params->fd_here_doc[*i - 1], str, ft_strlen(str));
		write(params->fd_here_doc[*i - 1], "\n", 1);
		free(str);
	}
	return (0);
}

int	ft_start_values_here_doc(t_params *params, t_list *list_commands)
{
	int	status;

	status = ft_here_doc_is_valid(list_commands, params);
	if (status != 0)
		return (status);
	params->fd_here_doc = (int *)malloc(sizeof(int) * params->count_here_doc);
	if (!params->fd_here_doc)
		return (12);
	params->name_here_doc = (char **)malloc(sizeof(char *)
			* params->count_here_doc);
	if (!params->name_here_doc)
	{
		free(params->fd_here_doc);
		return (12);
	}
	return (0);
}

int	ft_open_here_doc(int *i, t_params *params, t_list *list_commands)
{
	char	*str;

	str = ft_itoa((*i)++);
	if (!str)
		return (ft_if_error_here_doc(params, (*i) - 1, 12));
	params->name_here_doc[(*i) - 1]
		= ft_join_for_strs("here_doc_file_minishell_", str);
	free(str);
	if (!params->name_here_doc[(*i) - 1])
		return (ft_if_error_here_doc(params, (*i) - 1, 12));
	params->fd_here_doc[(*i) - 1] = open(params->name_here_doc[(*i) - 1],
			O_RDWR | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXO | S_IRWXG);
	if (params->fd_here_doc[(*i) - 1] < 0)
	{
		ft_if_error_here_doc(params, (*i), 0);
		ft_str_error("minishell: ", list_commands->next->name);
		params->error_is_printed = 1;
		return (errno);
	}
	return (0);
}
