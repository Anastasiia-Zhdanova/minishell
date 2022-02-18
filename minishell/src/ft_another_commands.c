/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_another_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 18:17:02 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/14 16:02:33 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parent_fork_no_pipes(t_params *params, int id_process)
{
	signal(SIGQUIT, ft_signal_quit);
	waitpid(id_process, &(params->status), 0);
	if (WIFEXITED(params->status))
		params->status = WEXITSTATUS(params->status);
	else if (WIFSIGNALED(params->status))
	{
		params->status = 128 + WTERMSIG(params->status);
		if (WTERMSIG(params->status) == SIGINT)
			printf("\n");
	}
	signal(SIGQUIT, SIG_IGN);
	params->error_is_printed = 1;
	return (params->status);
}

int	ft_fork_for_no_pipes(t_params *params)
{
	int		id_process;

	id_process = fork();
	if (id_process < -1)
		return (errno);
	else if (id_process != 0)
	{
		return (ft_parent_fork_no_pipes(params, id_process));
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		params->child = 1;
	}
	return (0);
}

int	ft_if_cmd_env_null(char **cmd, char **env,
			char	*path_cmd, t_list *list_commands)
{
	if (cmd == NULL || env == NULL)
	{
		if (path_cmd != list_commands->name)
			free (path_cmd);
		ft_check_arr_to_null(cmd);
		ft_check_arr_to_null(env);
		return (12);
	}
	return (0);
}

int	ft_access_command(t_list *list_commands, t_list **list_env, char **path_cmd)
{
	if (access(list_commands->name, F_OK) == 0)
		*path_cmd = list_commands->name;
	else
	{
		*path_cmd = ft_path(list_commands->name, *list_env);
		if (!(*path_cmd))
			return (12);
		if (ft_strcmp(*path_cmd, list_commands->name) == 0)
			return (127);
	}
	return (0);
}

int	ft_another_commands(t_list *list_commands,
				t_list **list_env, t_params *params)
{
	char	*path_cmd;
	char	**cmd;
	char	**env;
	int		status;

	if (params->count_pipes == 0 && params->child == 0)
	{
		status = ft_fork_for_no_pipes(params);
		if (params->child != 1)
			return (status);
	}
	status = ft_access_command(list_commands, list_env, &path_cmd);
	if (status != 0)
	{
		ft_write_err_another_com(params, list_commands);
		return (status);
	}
	cmd = ft_to_array_command(list_commands);
	env = ft_to_array_env(*list_env);
	if (ft_if_cmd_env_null(cmd, env, path_cmd, list_commands) != 0)
		return (12);
	execve(path_cmd, cmd, env);
	params->error_is_printed = 1;
	return (ft_str_error("minishell: ", cmd[0]));
}
