/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:29:02 by lwilliam          #+#    #+#             */
/*   Updated: 2023/03/09 18:29:16 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_check(t_minihell *mini)
{
	int	x;

	x = 0;
	while (mini->input_arr[x])
	{
		if (!ft_strncmp(mini->input_arr[x], ">", 2))
			right_redirect(mini, x);
		else if (!ft_strncmp(mini->input_arr[x], ">>", 3))
			right_append(mini, x);
		x++;
	}
	return (0);
}

void	right_redirect(t_minihell *mini, int x)
{
	int		fd;
	char	*tmp_msg;

	tmp_msg = ft_strdup(mini->input_arr[0]);
	fd = open(mini->input_arr[x + 1], O_CREAT | O_WRONLY, 0644);
	if (fd < 0)
	{
		printf("FD Error\n");
		return ;
	}
	dup2(fd, 1);
	close(fd);
	return ;
}

void	right_append(t_minihell *mini, int x)
{
	int		fd;
	char	*tmp_msg;

	tmp_msg = ft_strdup(mini->input_arr[0]);
	fd = open(mini->input_arr[x + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		printf("FD Error\n");
		return ;
	}
	dup2(fd, 1);
	close(fd);
	return ;
}
