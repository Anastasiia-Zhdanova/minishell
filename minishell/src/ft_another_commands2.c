/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_another_commands2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:48:45 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/12 23:03:26 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_if_arr_null(char **array, int i)
{
	if (!array[i])
	{
		while (i > 0)
		{
			free(array[i - 1]);
			i--;
		}
		free(array);
		return (NULL);
	}
	return (array[i]);
}

char	**ft_to_array_command(t_list *list)
{
	char	**array;
	int		size;
	int		i;

	size = ft_lstsize(list);
	array = (char **)malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (list != NULL)
	{
		array[i] = ft_strdup(list->name);
		if (ft_if_arr_null(array, i) == NULL)
			return (NULL);
		i++;
		list = list->next;
	}
	array[i] = NULL;
	return (array);
}

char	*ft_if_str_null(char *str_tmp, char **array, int i)
{
	if (!str_tmp)
	{
		while (i > 0)
		{
			free(array[i - 1]);
			i--;
		}
		free(array);
		return (NULL);
	}
	return (str_tmp);
}

char	**ft_to_array_env(t_list *list)
{
	char	**array;
	char	*str_tmp;
	int		size;
	int		i;

	size = ft_lstsize(list);
	array = (char **)malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (list != NULL)
	{
		array[i] = ft_join_for_strs(list->name, "=");
		if (ft_if_arr_null(array, i) == NULL)
			return (NULL);
		str_tmp = ft_join_for_strs(array[i], list->value);
		free(array[i]);
		if (ft_if_str_null(str_tmp, array, i) == NULL)
			return (NULL);
		array[i] = str_tmp;
		i++;
		list = list->next;
	}
	array[i] = NULL;
	return (array);
}

void	ft_write_err_another_com(t_params *params, t_list *list_commands)
{
	write(2, "minishell: ", 11);
	write(2, list_commands->name, ft_strlen(list_commands->name));
	write(2, ": command not found\n", 20);
	params->error_is_printed = 1;
}
