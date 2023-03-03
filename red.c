/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:19:53 by lwilliam          #+#    #+#             */
/*   Updated: 2023/03/01 13:54:37 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_red(t_minihell *mini)
{
	int	x;

	x = 0;
	while (mini->input_arr[x])
	{
		if (!ft_strncmp(mini->input_arr[x++], ">", 2))
			return (1);
	}
	return (0);
}

void	reading(t_minihell *mini)
{
	char	buffer[1024];
	ssize_t	n;

	// buffer = malloc(sizeof(char) * 1024);
	n = read(STDIN_FILENO, buffer, sizeof(buffer));
	if (n == -1)
	{
		perror("read");
		return ;
	}
	printf("Input: %.*s", (int)n, buffer);
	// free(buffer);
	return ;
}
