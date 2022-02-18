/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 12:24:42 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/11 16:04:14 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_sort_list_inside(char **name, char **value,
						t_list **next_el, t_list **current_el)
{
	*name = (*current_el)->name;
	*value = (*current_el)->value;
	(*current_el)->name = (*next_el)->name;
	(*current_el)->value = (*next_el)->value;
	(*next_el)->name = *name;
	(*next_el)->value = *value;
}

void	ft_sort_list(t_list *list_env)
{
	t_list	*current_el;
	t_list	*next_el;
	char	*name;
	char	*value;

	current_el = list_env;
	next_el = NULL;
	if (current_el == NULL)
		return ;
	else
	{
		while (current_el != NULL)
		{
			next_el = current_el->next;
			while (next_el != NULL)
			{
				if (ft_strcmp(current_el->name, next_el->name) > 0)
					ft_sort_list_inside(&name, &value, &next_el, &current_el);
				next_el = next_el->next;
			}
			current_el = current_el->next;
		}
	}
}
