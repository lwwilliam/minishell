/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wting <wting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 19:16:14 by wting             #+#    #+#             */
/*   Updated: 2023/03/24 14:34:00 by wting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_open_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			while (str[++i] != '\'')
				if (!str[i])
					return (1);
		if (str[i] == '"')
			while (str[++i] != '"')
				if (!str[i])
					return (1);
		++i;
	}
	return (0);
}

int	check_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			while (str[++i] != '\'')
				;
		if (str[i] == '"')
			while (str[++i] != '"')
				;
		if (str[i] == '|' && str[i + 1] && str[i + 1] == '|')
			return (1);
		++i;
	}
	return (0);
}

int	check_empty_pipe(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			while (str[++i] != '\'')
				;
		if (str[i] == '"')
			while (str[++i] != '"')
				;
		if (str[i] == '|')
		{
			while (str[i++])
			{
				if (str[i] != ' ' && str[i] != '|' && str[i] != '\0')
					break ;
				if (str[i] == '|' || str[i] == '\0')
					return (1);
			}
		}
	}
	return (0);
}

int	check_valid(char *str)
{
	if (check_open_quotes(str))
		return (1);
	if (check_pipe(str))
		return (1);
	if (check_empty_pipe(str))
		return (1);
	return (0);
}
