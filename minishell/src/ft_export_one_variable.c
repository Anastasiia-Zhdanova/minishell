/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_one_variable.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 18:40:38 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/12 23:03:26 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_if_flag_same_zero(int flag_same, char *name,
				char *value, t_list **list_env)
{
	t_list	*elem;

	if (flag_same == 0)
	{
		elem = ft_create_element(name, value);
		if (elem == NULL)
			return (12);
		ft_push_back(list_env, elem);
	}
	return (0);
}

int	ft_export_one_variable(t_list **list_env, char *name, char *value)
{
	int		flag_same;
	t_list	*head;

	flag_same = 0;
	head = *list_env;
	while (*list_env != NULL)
	{
		if (ft_strcmp((*list_env)->name, name) == 0)
		{
			flag_same = 1;
			if ((*list_env)->value != NULL)
				free((*list_env)->value);
			(*list_env)->value = ft_strdup(value);
			if (!(*list_env)->value)
				return (12);
			break ;
		}
		*list_env = (*list_env)->next;
	}
	*list_env = head;
	if (ft_if_flag_same_zero(flag_same, name, value, list_env) == 12)
		return (12);
	return (0);
}
