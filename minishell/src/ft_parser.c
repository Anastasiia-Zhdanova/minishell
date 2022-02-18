/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 11:58:03 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/12 23:03:27 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_write_error(t_params *params, char status)
{
	write(2, "minishell: ", 11);
	if (status == 'c')
		write(2, strerror(params->status_command),
			ft_strlen(strerror(params->status_command)));
	else if (status == 'p')
		write(2, strerror(params->status_parser),
			ft_strlen(strerror(params->status_parser)));
	write(2, "\n", 1);
	params->error_is_printed = 1;
}

void	ft_start_values(t_params *params, t_list **list_str)
{
	params->flag_exit = 0;
	params->status_parser = 0;
	params->status_command = 0;
	params->name_here_doc = NULL;
	*list_str = NULL;
	tcgetattr(0, &(params->start_consol));
	tcgetattr(0, &(params->consol_ignore));
	params->consol_ignore.c_lflag &= ~(ISIG);
	params->consol_ignore.c_lflag &= ~(ECHOCTL);
}

void	ft_main_readline(t_params *params, char	**str)
{
	params->error_is_printed = 0;
	params->child = 0;
	params->count_pipes = 0;
	params->count_here_doc = 0;
	signal(SIGINT, ft_signal_ctrl_c);
	tcsetattr(0, TCSANOW, &params->consol_ignore);
	*str = readline("minishell$ ");
	if (g_status_for_sig_int != 0)
	{
		params->status_command = g_status_for_sig_int;
		g_status_for_sig_int = 0;
	}
	tcsetattr(0, TCSANOW, &params->start_consol);
	signal(SIGINT, SIG_IGN);
}

void	ft_clean_and_exit(t_list **list_str, t_params *params)
{
	ft_free_list(*list_str);
	*list_str = NULL;
	params->flag_exit = 1;
	printf("exit\n");
}

int	ft_parser(t_list **list_env)
{
	char		*str;
	t_list		*list_str;
	t_params	params;

	ft_start_values(&params, &list_str);
	while (1)
	{
		ft_main_readline(&params, &str);
		if (str != NULL && ft_strcmp(str, "") != 0)
		{
			if (ft_parser_inside(&params, list_env, &str, &list_str) == -1)
				break ;
			ft_free_str_list(str, NULL, list_str, 0);
			list_str = NULL;
		}
		else if (str == NULL)
		{
			ft_clean_and_exit(&list_str, &params);
			break ;
		}
	}
	if (params.status_parser != 0)
		return (params.status_parser);
	else
		return (params.status_command);
}
