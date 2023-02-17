/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 00:04:37 by lwilliam          #+#    #+#             */
/*   Updated: 2023/02/17 19:39:42 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_first(char *str)
{
	int	x;

	x = 0;
	while (str[x] != '\0')
	{
		str[x] = str[x + 1];
		x++;
	}
}

void	echo(t_minihell *mini)
{
	int		x;
	char	*tmp;

	x = 0;
	while (mini->input_arr[++x])
	{
		if (mini->input_arr[x][0] == '$')
		{
			remove_first(mini->input_arr[x]);
			tmp = get_env(mini->env_ll, mini->input_arr[x]);
			printf("%s ", tmp);
		}
		else
			printf("%s ", mini->input_arr[x]);
	}
	printf("\n");
}
