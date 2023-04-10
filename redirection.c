/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:29:02 by lwilliam          #+#    #+#             */
/*   Updated: 2023/04/10 13:11:47 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	right_redirect(t_minihell *mini, int x, char *valid)
{
	int		fd;

	fd = open(mini->input_arr[x + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		g_err_code = 258;
		ft_putstr_fd(REDIR_ERR, 2);
		return (1);
	}
	if (!ft_strncmp(mini->input_arr[0], ">", 2))
		return (1);
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
		g_err_code = 258;
		ft_putstr_fd(REDIR_ERR, 2);
		return (1);
	}
	if (!ft_strncmp(mini->input_arr[0], ">>", 3))
		return (1);
	array_dup(mini);
	if (access(valid, X_OK) == 0 || builtin_check(mini) == 1)
		dup2(fd, 1);
	close(fd);
	return (0);
}

char	*get_file(char **in, int x)
{
	while (in[x++])
	{
		if (!ft_strncmp(in[x], "<", 2)
			|| !ft_strncmp(in[x], ">", 2)
			|| !ft_strncmp(in[x], ">>", 3)
			|| !ft_strncmp(in[x], "<<", 3))
			return (in[x - 1]);
	}
	return (in[x - 2]);
}

int	left_redirect(t_minihell *mini, int x, char *valid)
{
	int		fd;
	int		red_pos;
	char	*file;

	file = get_file(mini->input_arr, x);
	if (x == 0)
	{
		g_err_code = 258;
		ft_putstr_fd(REDIR_ERR, 2);
		return (1);
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		g_err_code = 1;
		printf("Minishell: no such file or directory\
: %s\n", mini->input_arr[x + 1]);
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
