/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:18:09 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/13 18:24:54 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_write_here_doc(char *str, t_params *params)
{
	write(2, str, ft_strlen(str));
	params->error_is_printed = 1;
	return (258);
}

int	ft_check_redir(t_list *list_commands, t_params *params)
{
	if (list_commands->next == NULL)
		return (ft_write_here_doc
			("minishell: syntax error near unexpected token `newline'\n",
				params));
	else if (ft_strcmp(list_commands->next->name, "<") == 0)
		return (ft_write_here_doc
			("minishell: syntax error near unexpected token `<'\n",
				params));
	else if (ft_strcmp(list_commands->next->name, ">") == 0)
		return (ft_write_here_doc
			("minishell: syntax error near unexpected token `>'\n",
				params));
	else if (ft_strcmp(list_commands->next->name, "<<") == 0)
		return (ft_write_here_doc
			("minishell: syntax error near unexpected token `<<'\n",
				params));
	else if (ft_strcmp(list_commands->next->name, ">>") == 0)
		return (ft_write_here_doc
			("minishell: syntax error near unexpected token `>>'\n",
				params));
	return (0);
}

int	ft_count_here_doc(t_list *list_commands)
{
	int	count;

	count = 0;
	while (list_commands != NULL)
	{
		if (ft_strcmp(list_commands->name, "<<") == 0)
			count++;
		list_commands = list_commands->next;
	}
	return (count);
}

int	ft_here_doc_is_valid(t_list *list_commands, t_params *params)
{
	int	status;

	while (list_commands != NULL)
	{
		if (ft_strcmp(list_commands->name, "<<") == 0
			|| ft_strcmp(list_commands->name, ">>") == 0
			|| ft_strcmp(list_commands->name, "<") == 0
			|| ft_strcmp(list_commands->name, ">") == 0)
		{
			status = ft_check_redir(list_commands, params);
			if (status != 0)
				return (status);
			list_commands = list_commands->next;
		}
		list_commands = list_commands->next;
	}
	return (0);
}

int	ft_if_error_here_doc(t_params *params, int i, int status)
{
	free(params->fd_here_doc);
	params->fd_here_doc = NULL;
	while (i > 0)
	{
		unlink(params->name_here_doc[i - 1]);
		free(params->name_here_doc[i - 1]);
		i--;
	}
	free(params->name_here_doc);
	params->name_here_doc = NULL;
	return (status);
}
