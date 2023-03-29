/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wting <wting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:22:17 by lwilliam          #+#    #+#             */
/*   Updated: 2023/03/29 19:43:38 by wting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_non_bin(t_minihell *mini, char **commands)
{
	int	tmp;

	if (heredoc_check(mini, 1) == 0)
	{
		tmp = open(".tmp", O_RDONLY);
		dup2(tmp, 0);
		close(tmp);
		not_builtin(mini, commands, 1);
	}
}

char	**arr_dup(char **dup)
{
	int		x;
	char	**arr;

	x = 0;
	while (dup[x++])
		;
	arr = ft_calloc(x + 1, sizeof(char *));
	x = 0;
	while (dup[x])
	{
		arr[x] = ft_strdup(dup[x]);
		x++;
	}
	return (arr);
}

void	command(t_minihell *mini, t_data *data, int exit_if_zero)
{
	int		builtin;
	char	**commands;
	int		term_in;
	int		term_out;

	term_in = dup(STDIN_FILENO);
	term_out = dup(STDOUT_FILENO);
	mini->input_arr = arr_dup(data->cmd);
	builtin = builtin_check(mini);
	commands = command_make(mini);
	if (redirect_check(mini, commands[0]) == 1)
		return (free_funct(commands));
	if (builtin == 1)
		command_handle(mini);
	else
		run_non_bin(mini, commands);
	free_funct(commands);
	if (exit_if_zero == 0)
		exit (0);
	dup2(term_in, 0);
	dup2(term_out, 1);
	close(term_in);
	close(term_out);
	free_funct(mini->input_arr);
}

void	run_dup(int tmp_read, t_minihell *mini, t_data *data)
{
	if (tmp_read == 0)
		dup2(data->fd[1], STDOUT_FILENO);
	else if (data->next != NULL)
	{
		dup2(tmp_read, STDIN_FILENO);
		dup2(data->fd[1], STDOUT_FILENO);
	}
	else
		dup2(tmp_read, STDIN_FILENO);
	command(mini, data, 0);
	close(data->fd[0]);
	close(data->fd[1]);
}

void	run(t_minihell *mini, t_data *data)
{
	int		tmp_read;

	if (mini->ll_len == 1)
	{
		command(mini, data, 1);
		return ;
	}
	tmp_read = dup(STDIN_FILENO);
	while (data != NULL)
	{
		data->fork = fork();
		if (data->fork == 0)
			run_dup(tmp_read, mini, data);
		else
			waitpid(data->fork, NULL, 0);
		close(tmp_read);
		tmp_read = dup(data->fd[0]);
		close(data->fd[0]);
		close(data->fd[1]);
		data = data->next;
	}
	close (tmp_read);
}
