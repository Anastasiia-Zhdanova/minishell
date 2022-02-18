/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_copy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 22:31:50 by mvirgini          #+#    #+#             */
/*   Updated: 2022/01/26 22:57:08 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

t_list	*ft_list_copy(t_list *lst_head, t_list *lst_last_el)
{
	t_list	*list_new;
	t_list	*elem;

	list_new = NULL;
	if (lst_head == NULL || lst_head == lst_last_el)
		return (NULL);
	while (lst_head != lst_last_el)
	{
		elem = ft_create_element(lst_head->name, lst_head->value);
		if (!elem)
		{
			ft_free_list(list_new);
			return (NULL);
		}
		ft_push_back(&list_new, elem);
		lst_head = lst_head->next;
	}
	return (list_new);
}
