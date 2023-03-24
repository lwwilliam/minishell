/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 00:04:37 by lwilliam          #+#    #+#             */
/*   Updated: 2023/03/24 18:13:35 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	echo(t_minihell *mini)
// {
// 	int		x;
// 	char	*line;
// 	char	*spc;
// 	char	*tmp;

// 	x = 0;
// 	tmp = ft_strdup("");
// 	while (mini->input_arr[++x])
// 	{
// 		if (!ft_strncmp(mini->input_arr[x], "-n", 2))
// 			continue ;
// 		else if (!ft_strncmp(mini->input_arr[x], "<", 2)
// 			|| !ft_strncmp(mini->input_arr[x], "<<", 3)
// 			|| !ft_strncmp(mini->input_arr[x], ">", 2)
// 			|| !ft_strncmp(mini->input_arr[x], ">>", 3))
// 			break ;
// 		else if (mini->input_arr[x] != 0)
// 		{
// 			line = strjoin_helper(tmp, mini->input_arr[x], 1, 0);
// 			if (!mini->input_arr[x + 1])
// 			{
// 				spc = ft_strdup(line);
// 				free(line);
// 			}
// 			else
// 				spc = strjoin_helper(line, " ", 1, 0);
// 			tmp = ft_strdup(spc);
// 			free(spc);
// 		}
// 	}
// 	if (ft_strncmp(mini->input_arr[1], "-n", 2))
// 	{
// 		line = strjoin_helper(tmp, "\n", 1, 0);
// 		tmp = ft_strdup(line);
// 		free(line);
// 	}
// 	write(1, tmp, ft_strlen(tmp));
// 	free (tmp);
// }

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
		else if (!ft_strncmp(arr[x], "<", 2)
			|| !ft_strncmp(arr[x], "<<", 3)
			|| !ft_strncmp(arr[x], ">", 2)
			|| !ft_strncmp(arr[x], ">>", 3))
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