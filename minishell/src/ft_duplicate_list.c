/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_duplicate_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 14:54:56 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/11 15:42:39 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_duplicate_list_inside(int flag_oldpwd, t_list **list_duplicate)
{
	t_list	*temp;

	if (flag_oldpwd == 0)
	{
		temp = ft_create_element("OLDPWD", NULL);
		if (temp == NULL)
			return (ft_free_str_list(NULL, NULL, *list_duplicate, 12));
		ft_push_back(list_duplicate, temp);
	}
	ft_sort_list(*list_duplicate);
	while (*list_duplicate != NULL)
	{
		if (ft_strcmp((*list_duplicate)->name, "_") != 0)
		{
			if ((*list_duplicate)->value != NULL)
				printf("declare -x %s=\"%s\"\n", (*list_duplicate)->name,
					(*list_duplicate)->value);
			else
				printf("declare -x %s\n", (*list_duplicate)->name);
		}
		*list_duplicate = (*list_duplicate)->next;
	}
	return (0);
}

int	ft_duplicate_list(t_list *list_env)
{
	t_list	*list_duplicate;
	t_list	*temp;
	int		flag_oldpwd;

	flag_oldpwd = 0;
	list_duplicate = NULL;
	while (list_env != NULL)
	{
		if (ft_strcmp(list_env->name, "OLDPWD") == 0)
			flag_oldpwd = 1;
		temp = ft_create_element(list_env->name, list_env->value);
		if (temp == NULL)
			return (ft_free_str_list(NULL, NULL, list_duplicate, 12));
		ft_push_back(&list_duplicate, temp);
		list_env = list_env->next;
	}
	if (ft_duplicate_list_inside(flag_oldpwd, &list_duplicate) == 12)
		return (12);
	return (ft_free_str_list(NULL, NULL, list_duplicate, 0));
}
