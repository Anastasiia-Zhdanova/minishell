/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbeata <lbeata@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 23:46:40 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/12 23:03:27 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_elem_push(char *name_tmp, char *value_tmp, t_list **list_args)
{
	t_list	*elem;

	elem = ft_create_element(name_tmp, value_tmp);
	if (elem == NULL)
		return (ft_free_str_list(value_tmp, name_tmp, *list_args, 12));
	ft_free_str_list(value_tmp, name_tmp, NULL, 0);
	ft_push_back(list_args, elem);
	return (0);
}

static int	ft_pars_for_export_inside(t_list *for_export, t_list **list_args)
{
	int		i;
	char	*name_tmp;
	char	*value_tmp;

	i = 0;
	while (for_export->name[i] != '\0')
	{
		if (for_export->name[i] == '=')
		{
			name_tmp = ft_substr(for_export->name, 0, i);
			if (!name_tmp)
				return (ft_free_str_list(NULL, NULL, *list_args, 12));
			value_tmp = ft_substr(for_export->name, i + 1,
					ft_strlen(for_export->name) - (i + 1));
			if (!value_tmp)
				return (ft_free_str_list(name_tmp, NULL, *list_args, 12));
			return (ft_elem_push(name_tmp, value_tmp, list_args));
		}
		i++;
	}
	return (0);
}

int	ft_pars_for_export(t_list *for_export, t_list **list_env)
{
	t_list	*list_args;
	int		status;

	list_args = NULL;
	while (for_export != NULL)
	{
		status = ft_pars_for_export_inside(for_export, &list_args);
		if (status != 0)
			return (status);
		for_export = for_export->next;
	}
	if (ft_export(list_env, list_args) == 12)
		return (ft_free_str_list(NULL, NULL, list_args, 12));
	return (ft_free_str_list(NULL, NULL, list_args, 0));
}

int	ft_export(t_list **list_env, t_list *to_add)
{
	if (to_add != NULL)
	{
		while (to_add != NULL)
		{
			if (ft_export_one_variable(list_env,
					to_add->name, to_add->value) == 12)
				return (12);
			to_add = to_add->next;
		}
	}
	else
	{
		if (*list_env == NULL)
			return (0);
		if (ft_duplicate_list(*list_env) == 12)
			return (12);
	}
	return (0);
}
