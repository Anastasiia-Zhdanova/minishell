/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 23:29:08 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/12 23:03:26 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_list	*list_env, int status)
{
	ft_free_list(list_env);
	if (status == -2 || status == 0)
		exit (0);
	if (status == 12)
		perror("minishell");
	exit (status);
}

static int	ft_write_error_exit(t_list *list_args)
{
	write (2, "minishell: exit: ", 17);
	write (2, list_args->name, ft_strlen(list_args->name));
	write (2, ": numeric argument required\n", 28);
	return (255);
}

int	ft_exit_command(t_list	*list_args, int status)
{
	int		flag_digit;
	char	*start_name;

	flag_digit = 0;
	printf("exit\n");
	if (list_args == NULL)
		return (status);
	else
	{
		start_name = list_args->name;
		while (*start_name != '\0')
		{
			if (ft_isdigit(*start_name) != 1)
				flag_digit = 1;
			start_name++;
		}
		if (flag_digit != 1)
			return (ft_atoi(list_args->name));
		else
			return (ft_write_error_exit(list_args));
	}
}

int	ft_free_str_list(char *str, char *str_s, t_list *list, int status)
{
	if (str != NULL)
		free(str);
	if (str_s != NULL)
		free(str_s);
	if (list != NULL)
		ft_free_list(list);
	return (status);
}
