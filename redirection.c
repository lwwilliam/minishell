/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:29:02 by lwilliam          #+#    #+#             */
/*   Updated: 2023/03/13 18:34:14 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	right_redirect(t_minihell *mini, int x, char *valid)
{
	int		fd;

	unlink(mini->input_arr[x + 1]);
	fd = open(mini->input_arr[x + 1], O_CREAT | O_WRONLY, 0644);
	if (fd < 0)
	{
		printf("Minishell: syntax error near unexpected token `newline'\n");
		return ;
	}
	if (access(valid, X_OK) == 0)
		dup2(fd, 1);
	close(fd);
	return ;
}

void	right_append(t_minihell *mini, int x, char *valid)
{
	int		fd;

	fd = open(mini->input_arr[x + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		printf("Minishell: syntax error near unexpected token `newline'\n");
		return ;
	}
	if (access(valid, X_OK) == 0)
		dup2(fd, 1);
	close(fd);
	return ;
}

void	left_redirect(t_minihell *mini, int x, char *valid)
{
	int		fd;

	fd = open(mini->input_arr[x + 1], O_RDONLY);
	if (fd < 0)
	{
		printf("Minishell: no such file or directory: %s\n",
			mini->input_arr[x + 1]);
		return ;
	}
	if (access(valid, X_OK) == 0)
		dup2(fd, 0);
	close(fd);
	return ;
}

int	redirect_check(t_minihell *mini, char *valid)
{
	int	x;

	x = 0;
	while (mini->input_arr[x])
	{
		if (!ft_strncmp(mini->input_arr[x], ">", 2))
			right_redirect(mini, x, valid);
		else if (!ft_strncmp(mini->input_arr[x], ">>", 3))
			right_append(mini, x, valid);
		else if (!ft_strncmp(mini->input_arr[x], "<", 2))
			left_redirect(mini, x, valid);
		x++;
	}
	return (0);
}

// cat
// <
// O_DIRECTORY 
// <
// ..
// <
// main.c

// ls