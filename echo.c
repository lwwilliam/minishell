/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 00:04:37 by lwilliam          #+#    #+#             */
/*   Updated: 2023/03/14 00:59:38 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_minihell *mini)
{
	int		x;

	x = 0;
	while (mini->input_arr[++x])
	{
		if (!ft_strncmp(mini->input_arr[x], "-n", 2))
			continue ;
		else if (!ft_strncmp(mini->input_arr[x], "<", 2)
			|| !ft_strncmp(mini->input_arr[x], "<<", 3)
			|| !ft_strncmp(mini->input_arr[x], ">", 2)
			|| !ft_strncmp(mini->input_arr[x], ">>", 3))
			break;
		else if (mini->input_arr[x] != 0)
			printf("%s ", mini->input_arr[x]);
	}
	if (ft_strncmp(mini->input_arr[1], "-n", 2))
		printf("\n");
	printf("\b");
}
