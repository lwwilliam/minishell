/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wting <wting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:22:17 by lwilliam          #+#    #+#             */
/*   Updated: 2023/04/18 23:36:47 by wting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command(t_minihell *mini, t_data *data, int exit_if_zero)
{
	int		builtin;
	char	**commands;

	mini->input_arr = arr_dup(data->cmd);
	builtin = builtin_check(mini);
	commands = command_make(mini);
	if (redirect_check(mini, commands[0]) == 1)
		return ;
	free_funct(commands);
	commands = command_make(mini);
	if (builtin == 1)
		command_handle(mini, exit_if_zero);
	else
		run_bin(mini, commands, exit_if_zero);
	if (exit_if_zero == 0)
		exit (0);
	free_funct(commands);
	free_funct(mini->input_arr);
}

void	run_dup(int *tmp_read, t_minihell *mini, t_data *data, t_data *first)
{
	if (*tmp_read == -2)
		dup2(data->fd[1], STDOUT_FILENO);
	else if (data->next != NULL)
	{
		if (!data->heredoc_zero_if_valid)
			dup2(*tmp_read, STDIN_FILENO);
		dup2(data->fd[1], STDOUT_FILENO);
	}
	else
	{
		if (!data->heredoc_zero_if_valid)
			dup2(*tmp_read, STDIN_FILENO);
	}
	close_all_pipes(first);
	command(mini, data, 0);
}

void	run_heredoc(t_minihell *mini, t_data *data)
{
	int	tmp;

	data->term_in = dup(STDIN_FILENO);
	data->term_out = dup(STDOUT_FILENO);
	data->heredoc_zero_if_valid = heredoc_check(mini);
	if (data->heredoc_zero_if_valid == 0)
	{
		tmp = open(".tmp", O_RDONLY);
		dup2(tmp, 0);
		close(tmp);
	}
}

void	run_pipes(t_minihell *mini, t_data *data, t_data *first)
{
	int	tmp_read;

	tmp_read = -2;
	while (data != NULL)
	{
		pre_fork(mini, data);
		data->fork = fork();
		if (data->fork == 0)
		{
			run_dup(&tmp_read, mini, data, first);
			exit(1);
		}
		else if (data->fork == -1)
		{
			ft_putstr_fd("Fork failed\n", 2);
			exit (1);
		}
		waitpid(0, &mini->err_stat, -1);
		if (data->next != NULL)
			tmp_read = data->fd[0];
		term_reset(data);
		data = data->next;
	}
}

void	run(t_minihell *mini, t_data *data)
{
	int		tmp_read;
	t_data	*head;
	t_data	*first;

	if (!run_no_pipes(mini, data))
		return ;
	tmp_read = -2;
	first = data;
	run_pipes(mini, data, first);
	close_all_pipes(first);
	head = first;
	while (head != NULL)
	{
		waitpid(head->fork, &mini->err_stat, WUNTRACED);
		g_err_code = mini->err_stat % 255;
		if (WIFSIGNALED(mini->err_stat))
			g_err_code = (WTERMSIG(mini->err_stat) + 128);
		head = head->next;
	}
}
