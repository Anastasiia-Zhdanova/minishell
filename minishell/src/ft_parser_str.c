/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbeata <lbeata@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 10:52:59 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/13 19:09:36 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_start_values(t_list **list_str, char **str_tmp,
				int *single_quote, int *double_quote)
{
	*single_quote = 0;
	*double_quote = 0;
	*list_str = NULL;
	*str_tmp = (char *)malloc(sizeof(char));
	if (!(*str_tmp))
		return (12);
	**str_tmp = '\0';
	return (0);
}

void	ft_check_quote(int *quote)
{
	if (*quote == 1)
		*quote = 0;
	else
		*quote = 1;
}

int	ft_else(char **str_tmp, char *str)
{
	char	*str_tmp_addr;

	str_tmp_addr = ft_strjoin(*str_tmp, *str);
	if (!str_tmp_addr)
		return (ft_free_str_list(*str_tmp, NULL, NULL, 12));
	free(*str_tmp);
	*str_tmp = str_tmp_addr;
	return (0);
}

int	ft_parser_str_inside(t_quotes q, t_list **list_str,
			char **str_tmp, char *str)
{
	if (ft_is_space(*str) == 1 && q.single_quote != 1
		&& q.double_quote != 1)
	{
		if (ft_space(str_tmp, list_str) == 12)
			return (12);
	}
	else if (ft_else(str_tmp, str) == 12)
		return (12);
	return (0);
}

int	ft_parser_str(char *str, t_list **list_env, t_list **list_str, int status)
{
	char		*str_tmp;
	t_quotes	q;

	if (ft_start_values(list_str, &str_tmp,
			&q.single_quote, &q.double_quote) == 12)
		return (12);
	while (*str != '\0')
	{
		if (*str == '"' && q.single_quote != 1)
			ft_check_quote(&q.double_quote);
		else if (*str == '\'' && q.double_quote != 1)
			ft_check_quote(&q.single_quote);
		else if (*str == '$' && q.single_quote != 1)
		{
			if (ft_dollar(&str, list_env, &str_tmp, status) == 12)
				return (12);
			continue ;
		}
		else if (ft_parser_str_inside(q, list_str, &str_tmp, str) == 12)
			return (12);
		if (*str != '\0')
			str++;
	}
	return (ft_another_simbols(&str_tmp, list_str,
			q.single_quote, q.double_quote));
}
