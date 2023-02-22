/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 00:04:37 by lwilliam          #+#    #+#             */
/*   Updated: 2023/02/20 18:08:01 by lwilliam         ###   ########.fr       */
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
		if (ft_strncmp(mini->input_arr[x], "(null)", 6))
			printf("%s ", mini->input_arr[x]);
	}
	printf("\n");
}
