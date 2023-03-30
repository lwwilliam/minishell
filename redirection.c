/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wting <wting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:29:02 by lwilliam          #+#    #+#             */
/*   Updated: 2023/03/29 20:57:07 by wting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	array_dup(t_minihell *mini)
{
	char	**dup;
	int		x;
	int		y;

	y = 0;
	x = 0;
	dup = mal_dup(mini);
	while (mini->input_arr[x])
	{
		if (!is_redir(mini->input_arr[x]))
			x += 2;
		else
			dup[y++] = ft_strdup(mini->input_arr[x++]);
	}
	x = -1;
	while (mini->input_arr[++x])
	{
		if (!is_redir(mini->input_arr[x]))
		{
			dup[y++] = ft_strdup(mini->input_arr[x++]);
			dup[y++] = ft_strdup(mini->input_arr[x]);
		}
	}
	free_funct(mini->input_arr);
	mini->input_arr = dup;
}

int	right_redirect(t_minihell *mini, int x, char *valid)
{
	int		fd;

	fd = open(mini->input_arr[x + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("Minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	array_dup(mini);
	if (access(valid, X_OK) == 0 || builtin_check(mini) == 1)
		dup2(fd, 1);
	close(fd);
	return (0);
}

int	right_append(t_minihell *mini, int x, char *valid)
{
	int		fd;

	fd = open(mini->input_arr[x + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		printf("Minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	array_dup(mini);
	if (access(valid, X_OK) == 0 || builtin_check(mini) == 1)
		dup2(fd, 1);
	close(fd);
	return (0);
}

int	left_redirect(t_minihell *mini, int x, char *valid)
{
	int		fd;

	while (mini->input_arr[x++])
		;
	fd = open(mini->input_arr[x - 2], O_RDONLY);
	if (fd < 0)
	{
		printf("Minishell: no such file or directory: %s\n",
			mini->input_arr[x + 1]);
		return (1);
	}
	if (access(valid, X_OK) == 0 || builtin_check(mini) == 1)
		dup2(fd, 0);
	close(fd);
	return (0);
}

int	redirect_check(t_minihell *mini, char *valid)
{
	int	x;
	int	err;

	x = 0;
	err = 0;
	while (mini->input_arr[x])
	{
		if (!ft_strncmp(mini->input_arr[x], ">", 2))
			err = right_redirect(mini, x, valid);
		else if (!ft_strncmp(mini->input_arr[x], ">>", 3))
			err = right_append(mini, x, valid);
		else if (!ft_strncmp(mini->input_arr[x], "<", 2))
			err = left_redirect(mini, x, valid);
		if (err == 1)
			return (1);
		x++;
	}
	return (0);
}
