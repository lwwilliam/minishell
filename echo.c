/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wting <wting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 00:04:37 by lwilliam          #+#    #+#             */
/*   Updated: 2023/03/24 16:34:25 by wting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_minihell *mini)
{
	int		x;
	char	*tmp;
	char	*line;

	x = 0;
	line = ft_strdup("");
	while (mini->input_arr[++x])
	{
		if (!ft_strncmp(mini->input_arr[x], "-n", 2))
			continue ;
		else if (!ft_strncmp(mini->input_arr[x], "<", 2)
			|| !ft_strncmp(mini->input_arr[x], "<<", 3)
			|| !ft_strncmp(mini->input_arr[x], ">", 2)
			|| !ft_strncmp(mini->input_arr[x], ">>", 3))
			break ;
		else if (mini->input_arr[x] != 0)
		{
			tmp = strjoin_helper(line, mini->input_arr[x], 1, 0);
			line = strjoin_helper(tmp, " ", 1, 0);
		}
	}
	if (ft_strncmp(mini->input_arr[1], "-n", 2))
		tmp = strjoin_helper(line, "\n", 1, 0);
	write(1, tmp, ft_strlen(tmp));
	free (tmp);
}
