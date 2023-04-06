/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 00:04:37 by lwilliam          #+#    #+#             */
/*   Updated: 2023/04/05 15:01:02 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check(char *str)
{
	if (!ft_strncmp(str, "<", 2)
		|| !ft_strncmp(str, "<<", 3)
		|| !ft_strncmp(str, ">", 2)
		|| !ft_strncmp(str, ">>", 3))
		return (1);
	return (0);
}

char	*ret_line(char **arr)
{
	char	*tmp;
	char	*line;
	int		x;

	x = 0;
	line = ft_strdup("");
	while (arr[++x])
	{
		if (!ft_strncmp(arr[x], "-n", 2))
			continue ;
		else if (check(arr[x]) == 1)
			break ;
		else if (arr[x] != 0)
		{
			tmp = strjoin_helper(line, arr[x], 1, 0);
			if (!arr[x + 1])
			{
				line = ft_strdup(tmp);
				free(tmp);
			}
			else
				line = strjoin_helper(tmp, " ", 1, 0);
		}
	}
	return (line);
}

void	echo(t_minihell *mini)
{
	char	*tmp;
	char	*line;

	line = ret_line(mini->input_arr);
	if (ft_strncmp(mini->input_arr[1], "-n", 2))
	{
		tmp = strjoin_helper(line, "\n", 1, 0);
		line = ft_strdup(tmp);
		free(tmp);
	}
	write(1, line, ft_strlen(line));
	free (line);
}
