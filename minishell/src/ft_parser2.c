/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:00:45 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/12 23:03:26 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parser_inside(t_params *params, t_list **list_env,
						char **str, t_list **list_str)
{
	add_history(*str);
	if (params->status_parser != 0)
		params->status_parser = ft_parser_str(*str, list_env,
				list_str, params->status_parser);
	else
		params->status_parser = ft_parser_str(*str, list_env,
				list_str, params->status_command);
	if (params->status_parser == 12)
	{
		ft_free_list(*list_str);
		free((void *)(*str));
		*list_str = NULL;
		return (-1);
	}
	else if (params->status_parser != 0)
		ft_write_error(params, 'p');
	else
	{
		if (ft_start_here_doc_pipes(params, list_str, str, list_env) == -1)
			return (-1);
	}
	return (0);
}

int	ft_call_pipex(t_params *params, t_list **list_str,
				char **str, t_list **list_env)
{
	params->status_command = ft_pipex(*list_str, list_env, params);
	if (params->status_command != 0 && params->error_is_printed == 0)
		ft_write_error(params, 'c');
	if (params->child != 1)
		ft_delete_tmp_files(params);
	if (params->child == 1 || params->flag_exit == 1
		|| params->status_command == 12)
	{
		free((void *)(*str));
		ft_free_list(*list_str);
		*list_str = NULL;
		return (-1);
	}
	return (0);
}

int	ft_check_if_pipe(t_params *params, t_list **list_str,
						char **str, t_list **list_env)
{
	if (params->count_pipes == 0)
	{
		params->status_command = ft_redirect(*list_str, params, list_env);
		if (params->child != 1)
			ft_delete_tmp_files(params);
		if (params->flag_exit == 1 || params->status_command == 12
			|| params->child == 1)
		{
			free((void *)(*str));
			ft_free_list(*list_str);
			*list_str = NULL;
			return (-1);
		}
	}
	else
	{
		if (ft_call_pipex(params, list_str, str, list_env) == -1)
			return (-1);
	}
	return (0);
}

int	ft_start_here_doc_pipes(t_params *params, t_list **list_str,
							char **str, t_list **list_env)
{
	params->status_command = ft_here_doc(*list_str, params);
	if (params->status_command == 12 || params->child == 1)
	{
		free((void *)(*str));
		ft_free_list(*list_str);
		*list_str = NULL;
		return (-1);
	}
	else if (params->status_command != 0)
	{
		if (params->error_is_printed == 0)
			ft_write_error(params, 'c');
	}
	else
	{
		params->count_pipes = ft_count_pipes(*list_str);
		if (ft_check_if_pipe(params, list_str, str, list_env) == -1)
			return (-1);
	}
	return (0);
}
