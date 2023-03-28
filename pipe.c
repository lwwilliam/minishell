/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wting <wting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:22:17 by lwilliam          #+#    #+#             */
/*   Updated: 2023/03/28 21:28:42 by wting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command(t_minihell *mini, t_data *data, int exit_if_zero)
{
	int		builtin;
	int		tmp;
	char	**commands;

	mini->input_arr = data->cmd;
	builtin = builtin_check(mini);
	commands = command_make(mini);
	redirect_check(mini, commands[0]);
	if (builtin == 1)
		command_handle(mini);
	else
	{
		if (heredoc_check(mini, 1) == 0)
		{
			tmp = open(".tmp", O_RDONLY);
			dup2(tmp, 0);
			close(tmp);
			not_builtin(mini, commands, 1);
		}
	}
	free_funct(commands);
	if (exit_if_zero == 0)
		exit (0);
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
