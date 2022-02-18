/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_str2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 00:12:45 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/13 00:12:45 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_space(char simbol)
{
	if ((simbol == ' ') || (simbol == '\f') || (simbol == '\n')
		|| (simbol == '\r') || (simbol == '\t') || (simbol == '\v'))
	{
		return (1);
	}
	return (0);
}

int	ft_find_env(char *str_dollar, t_list *env, char **str)
{
	size_t	len;
	int		i;
	char	*str_tmp_addr;

	i = 0;
	while (env != NULL)
	{
		if (ft_strcmp(env->name, str_dollar) == 0)
		{
			len = ft_strlen(env->value);
			while (len > 0)
			{
				str_tmp_addr = ft_strjoin(*str, (env->value)[i++]);
				if (!str_tmp_addr)
					return (12);
				free(*str);
				*str = str_tmp_addr;
				len--;
			}
			break ;
		}
		env = env->next;
	}
	return (0);
}
