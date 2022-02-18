/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_delete_elem_list.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 23:52:36 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/10 18:54:09 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_if_value_null(t_list *elem)
{
	if (elem->value == NULL)
	{
		free(elem->name);
		free(elem);
		return (NULL);
	}
	return (elem->value);
}

t_list	*ft_create_element(char *name, char *value)
{
	t_list	*elem;

	elem = (t_list *)(malloc(sizeof(t_list)));
	if (elem != NULL)
	{
		elem->name = ft_strdup(name);
		if (elem->name == NULL)
		{
			free(elem);
			return (NULL);
		}
		if (value == NULL)
			elem->value = value;
		else
		{
			elem->value = ft_strdup(value);
			if (ft_if_value_null(elem) == NULL)
				return (NULL);
		}
		elem->next = NULL;
		return (elem);
	}
	else
		return (NULL);
}

void	ft_delete_element(t_list *to_del, t_list **head)
{
	t_list	*list_tmp;

	list_tmp = *head;
	if (list_tmp == to_del)
		*head = list_tmp->next;
	else
	{
		while (list_tmp->next != to_del && list_tmp->next != NULL)
			list_tmp = list_tmp->next;
		list_tmp->next = to_del->next;
	}
	if (to_del->name != NULL)
		free(to_del->name);
	if (to_del->value != NULL)
		free(to_del->value);
	free(to_del);
}

void	ft_free_list(t_list *list)
{
	t_list				*elem;
	t_list				*elem_tmp;

	elem = list;
	while (elem != NULL)
	{
		elem_tmp = elem->next;
		ft_delete_element(elem, &list);
		elem = elem_tmp;
	}
}
