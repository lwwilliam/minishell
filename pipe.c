/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:22:17 by lwilliam          #+#    #+#             */
/*   Updated: 2023/04/13 17:34:51 by lwilliam         ###   ########.fr       */
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
		return (free_funct(commands));
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
		dup2(*tmp_read, STDIN_FILENO);
		dup2(data->fd[1], STDOUT_FILENO);
	}
	else
	{
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
	mini->input_arr = arr_dup(data->cmd);
	if (heredoc_check(mini) == 0)
	{
		tmp = open(".tmp", O_RDONLY);
		dup2(tmp, 0);
		close(tmp);
	}
	free_funct(mini->input_arr);
}

void	run_pipes(t_minihell *mini, t_data *data, t_data *first)
{
	int	tmp_read;

	tmp_read = -2;
	while (data != NULL)
	{
		run_heredoc(mini, data);
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
		waitpid(0, 0, -1);
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

	if (mini->ll_len == 1)
	{
		run_heredoc(mini, data);
		command(mini, data, 1);
		term_reset(data);
		return ;
	}
	tmp_read = -2;
	first = data;
	run_pipes(mini, data, first);
	close_all_pipes(first);
	head = first;
	while (head != NULL)
	{
		waitpid(-1, NULL, WUNTRACED);
		head = head->next;
	}
}
