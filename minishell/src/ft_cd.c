/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 15:27:10 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/12 23:14:49 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env_value(t_list *list_env, char *name)
{
	while (list_env != NULL)
	{
		if (ft_strcmp(list_env->name, name) == 0)
			return (list_env->value);
		list_env = list_env->next;
	}
	return (NULL);
}

static int	ft_cd_oldpwd(char *path_str, t_list **list_env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (ft_str_error("minishell: cd", NULL));
	if (chdir(path_str) == -1)
	{
		free(pwd);
		return (ft_str_error("minishell: cd: ", path_str));
	}
	if (ft_export_one_variable(list_env, "OLDPWD", pwd) == 12)
	{
		free(pwd);
		return (12);
	}
	free(pwd);
	return (0);
}

static int	ft_cd_home_or_not(t_list *path, char **path_str, t_list **list_env)
{
	if (path == NULL)
	{
		*path_str = ft_get_env_value(*list_env, "HOME");
		if (*path_str == NULL || ft_strcmp(*path_str, "") == 0)
		{
			printf("minishell: cd: HOME not set\n");
			return (1);
		}
	}
	else
		*path_str = path->name;
	return (0);
}

int	ft_cd(t_list *path, t_list **list_env)
{
	char	*pwd;
	char	*path_str;
	int		status;

	status = ft_cd_home_or_not(path, &path_str, list_env);
	if (status != 0)
		return (status);
	status = ft_cd_oldpwd(path_str, list_env);
	if (status != 0)
		return (status);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (ft_str_error("minishell: cd", NULL));
	if (ft_export_one_variable(list_env, "PWD", pwd) == 12)
	{
		free(pwd);
		return (12);
	}
	free(pwd);
	return (0);
}
