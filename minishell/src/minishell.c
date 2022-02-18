/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbeata <lbeata@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 17:21:11 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/12 23:03:26 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_wrong_args(int argc)
{
	if (argc != 1)
	{
		write(2, "too many arguments, write './minishell'\n", 40);
		exit(1);
	}
}

int	main(int argc, char	*argv[], char *envp[])
{
	int		status;
	t_list	*list_env;

	status = 0;
	(void)argv;
	ft_wrong_args(argc);
	g_status_for_sig_int = 0;
	status = ft_parser_env(envp, &list_env);
	if (status != 0)
	{
		perror("minishell");
		exit(status);
	}
	signal(SIGQUIT, SIG_IGN);
	status = ft_parser(&list_env);
	if (status != 0)
		ft_exit(list_env, status);
	ft_exit(list_env, 0);
	return (0);
}
