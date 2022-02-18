/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:01:03 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/12 23:03:27 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_if_export(t_list *list_commands,
			t_list **list_env, t_params *params)
{
	int	status;

	status = ft_pars_for_export(list_commands->next, list_env);
	if (status != 0)
	{
		if (status == 12)
			params->flag_exit = 1;
		return (status);
	}
	return (0);
}

static int	ft_if_pwd(t_params *params)
{
	int		status;

	status = ft_pwd();
	if (status != 0)
	{
		if (status == 12)
			params->flag_exit = 1;
		return (status);
	}
	return (0);
}

static int	ft_if_cd(t_list *list_commands,
					t_list **list_env, t_params *params)
{
	int		status;

	status = ft_cd(list_commands->next, list_env);
	if (status != 0)
	{
		if (status == 12)
			params->flag_exit = 1;
		return (status);
	}
	return (0);
}

int	ft_execute_command(t_list *list_commands,
			t_list **list_env, t_params *params)
{
	if (list_commands != NULL)
	{
		if (ft_strcmp(list_commands->name, "export") == 0)
			return (ft_if_export(list_commands, list_env, params));
		else if (ft_strcmp(list_commands->name, "pwd") == 0)
			return (ft_if_pwd(params));
		else if (ft_strcmp(list_commands->name, "cd") == 0)
			return (ft_if_cd(list_commands, list_env, params));
		else if (ft_strcmp(list_commands->name, "env") == 0)
			ft_env(*list_env);
		else if (ft_strcmp(list_commands->name, "exit") == 0)
		{
			params->flag_exit = 1;
			return (ft_exit_command(list_commands->next,
					params->status_command));
		}
		else if (ft_strcmp(list_commands->name, "unset") == 0)
			ft_unset(list_commands->next, list_env);
		else if (ft_strcmp(list_commands->name, "echo") == 0)
			ft_echo(list_commands->next);
		else
			return (ft_another_commands(list_commands, list_env, params));
	}
	return (0);
}
