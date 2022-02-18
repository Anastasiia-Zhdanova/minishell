/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 23:44:38 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/12 23:03:27 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_list *list_args, t_list	**list_env)
{
	t_list	*head;

	if (list_args == NULL)
		return ;
	else
	{
		while (list_args != NULL)
		{
			head = *list_env;
			while (head != NULL)
			{
				if (ft_strcmp(list_args->name, head->name) == 0)
				{
					ft_delete_element(head, list_env);
					break ;
				}
				head = head->next;
			}
			list_args = list_args->next;
		}
	}
}
