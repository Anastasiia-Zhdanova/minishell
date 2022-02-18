/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbeata <lbeata@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 18:27:03 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/12 23:03:27 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strdup_path(char *str, int n)
{
	int		i;
	char	*dup_s;

	i = 0;
	dup_s = (char *)malloc((n + 1) * sizeof(char));
	if (dup_s == NULL)
		return (NULL);
	while (i < n)
		dup_s[i++] = *str++;
	dup_s[n] = '\0';
	return (dup_s);
}

static char	*ft_path_inside(t_list *list_env)
{
	while (list_env != NULL)
	{
		if (ft_strcmp(list_env->name, "PATH") == 0)
			return (list_env->value);
		list_env = list_env->next;
	}
	return (NULL);
}

static int	ft_try_paths(char **path, char **bin, char **dir, char **cmd)
{
	while (**path != '\0' && ft_strchr(*path, ':') > -1)
	{
		*dir = ft_strdup_path(*path, ft_strchr(*path, ':'));
		if (*dir == NULL)
			return (0);
		*bin = ft_strjoin_path(*dir, *cmd);
		free(*dir);
		if (*bin == NULL)
			return (0);
		if (access(*bin, F_OK) == 0)
			return (1);
		free(*bin);
		*path += ft_strchr(*path, ':') + 1;
	}
	return (2);
}

char	*ft_path(char *cmd, t_list *list_env)
{
	char	*path;
	char	*bin;
	char	*dir;
	int		status;

	path = ft_path_inside(list_env);
	if (path == NULL)
		return (cmd);
	status = ft_try_paths(&path, &bin, &dir, &cmd);
	if (status == 0)
		return (NULL);
	else if (status == 1)
		return (bin);
	if (*path != '\0')
	{
		bin = ft_strjoin_path(path, cmd);
		if (!bin)
			return (NULL);
		if (access(bin, F_OK) == 0)
			return (bin);
		free (bin);
	}
	return (cmd);
}
