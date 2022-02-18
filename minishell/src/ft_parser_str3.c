/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_str3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 19:10:20 by mvirgini          #+#    #+#             */
/*   Updated: 2022/02/13 19:17:02 by mvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_space(char **str_tmp, t_list **list_str)
{
	t_list	*elem;

	if (**str_tmp != '\0')
	{
		elem = ft_create_element(*str_tmp, NULL);
		if (elem == NULL)
			return (ft_free_str_list(*str_tmp, NULL, NULL, 12));
		free(*str_tmp);
		ft_push_back(list_str, elem);
		*str_tmp = (char *)malloc(sizeof(char));
		if (!(*str_tmp))
			return (12);
		**str_tmp = '\0';
	}
	return (0);
}

int	ft_if_question(char **str, char **str_tmp, int status)
{
	int		i;
	int		len;
	char	*str_dollar;
	char	*str_tmp_addr;

	str_tmp_addr = ft_itoa(status);
	if (!str_tmp_addr)
		return (ft_free_str_list(*str_tmp, NULL, NULL, 12));
	len = ft_strlen(str_tmp_addr);
	i = 0;
	while (len > 0)
	{
		str_dollar = ft_strjoin(*str_tmp, str_tmp_addr[i++]);
		if (!str_dollar)
			return (ft_free_str_list(*str_tmp, str_tmp_addr,
					NULL, 12));
		free(*str_tmp);
		*str_tmp = str_dollar;
		len--;
	}
	free(str_tmp_addr);
	(*str)++;
	return (0);
}

int	ft_argument(char **str, char **str_tmp, t_list **list_env)
{
	char	*str_dollar;
	char	*str_tmp_addr;

	str_dollar = (char *)malloc(sizeof(char));
	*str_dollar = '\0';
	while (**str != '"' && ft_is_space(**str) != 1
		&& **str != '\0' && **str != '$')
	{
		str_tmp_addr = ft_strjoin(str_dollar, **str);
		if (!str_tmp_addr)
			return (ft_free_str_list(*str_tmp, str_dollar,
					NULL, 12));
		free(str_dollar);
		str_dollar = str_tmp_addr;
		(*str)++;
	}
	if (ft_find_env(str_dollar, *list_env, str_tmp) == 12)
		return (ft_free_str_list(*str_tmp, str_dollar, NULL, 12));
	free(str_dollar);
	return (0);
}

int	ft_another_simbols(char **str_tmp, t_list **list_str,
				int single_quote, int double_quote)
{
	t_list	*elem;

	if (**str_tmp != '\0' && single_quote != 1 && double_quote != 1)
	{
		elem = ft_create_element(*str_tmp, NULL);
		if (elem == NULL)
			return (ft_free_str_list(*str_tmp, NULL, NULL, 12));
		free(*str_tmp);
		ft_push_back(list_str, elem);
	}
	else if (single_quote == 1 || double_quote == 1)
	{
		free(*str_tmp);
		return (5);
	}
	return (0);
}

int	ft_dollar(char **str, t_list **list_env, char **str_tmp, int status)
{
	(*str)++;
	if (**str == '?')
	{
		if (ft_if_question(str, str_tmp, status) == 12)
			return (12);
	}
	else
	{
		if (ft_argument(str, str_tmp, list_env) == 12)
			return (12);
	}
	return (0);
}
