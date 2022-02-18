/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_tmp_files.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbeata <lbeata@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 11:38:49 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/12 23:03:27 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delete_tmp_files(t_params *params)
{
	int	i;

	i = params->count_here_doc;
	while (i > 0)
	{
		if (params->child != 1)
			unlink(params->name_here_doc[i - 1]);
		free(params->name_here_doc[i - 1]);
		i--;
	}
	free(params->name_here_doc);
	params->name_here_doc = NULL;
	params->count_here_doc = 0;
}
