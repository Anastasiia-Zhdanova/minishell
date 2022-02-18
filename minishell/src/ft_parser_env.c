/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 10:59:21 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/13 20:00:31 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_shlvl_zero(int shlvl_status, t_list **list_env)
{
	t_list	*elem;

	if (shlvl_status == 0)
	{
		elem = ft_create_element("SHLVL", "1");
		if (elem == NULL)
			return (ft_free_str_list(NULL, NULL, *list_env, 12));
		ft_push_back(list_env, elem);
	}
	return (0);
}

int	ft_add_el_in_list_env(char *name_tmp, char *value_tmp, t_list **list_env)
{
	t_list	*elem;

	elem = ft_create_element(name_tmp, value_tmp);
	if (elem == NULL)
		return (ft_free_str_list(value_tmp, name_tmp, *list_env, 12));
	ft_free_str_list(value_tmp, name_tmp, NULL, 0);
	ft_push_back(list_env, elem);
	return (0);
}

int	ft_if_shlvl(t_env *vars, char *env, t_list **list_env, int j)
{
	vars->shlvl_status = 1;
	vars->value_tmp = ft_substr(env, j + 1, ft_strlen(env) - (j + 1));
	if (!vars->value_tmp)
		return (ft_free_str_list(vars->name_tmp, NULL, *list_env, 12));
	vars->shlvl = ft_atoi(vars->value_tmp) + 1;
	free(vars->value_tmp);
	vars->value_tmp = ft_itoa(vars->shlvl);
	if (!vars->value_tmp)
		return (ft_free_str_list(vars->name_tmp, NULL, *list_env, 12));
	return (0);
}

int	ft_parser_env_inside(t_env *vars, t_list **list_env, char **env)
{
	vars->name_tmp = ft_substr(env[vars->i], 0, vars->j);
	if (!vars->name_tmp)
		return (ft_free_str_list(NULL, NULL, *list_env, 12));
	if (ft_strcmp(vars->name_tmp, "OLDPWD") == 0)
	{
		free(vars->name_tmp);
		return (0);
	}
	else if (ft_strcmp(vars->name_tmp, "SHLVL") == 0)
	{
		if (ft_if_shlvl(vars, env[vars->i], list_env, vars->j) == 12)
			return (12);
	}
	else
	{
		vars->value_tmp = ft_substr(env[vars->i], vars->j + 1,
				ft_strlen(env[vars->i]) - (vars->j + 1));
		if (!vars->value_tmp)
			return (ft_free_str_list(vars->name_tmp, NULL, *list_env, 12));
	}
	if (ft_add_el_in_list_env(vars->name_tmp, vars->value_tmp, list_env) == 12)
		return (12);
	return (0);
}

int	ft_parser_env(char **env, t_list **list_env)
{
	t_env	vars;

	vars.shlvl_status = 0;
	*list_env = NULL;
	vars.i = 0;
	while (env[vars.i] != NULL)
	{
		vars.j = 0;
		while (env[vars.i][vars.j] != '\0')
		{
			if (env[vars.i][vars.j] == '=')
			{
				if (ft_parser_env_inside(&vars, list_env, env) == 12)
					return (12);
				break ;
			}
			vars.j++;
		}
		vars.i++;
	}
	if (ft_shlvl_zero(vars.shlvl_status, list_env) == 12)
		return (12);
	return (0);
}
