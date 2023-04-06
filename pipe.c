/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:22:17 by lwilliam          #+#    #+#             */
/*   Updated: 2023/04/05 16:09:38 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	piped_not_builtin(t_minihell *mini, char **commands)
{
	char	**env;

	env = env_2d(mini->env_ll);
	execve(commands[0], commands, env);
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(mini->input_arr[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(1);
}

void	run_non_bin(t_minihell *mini, char **commands)
{
	int	tmp;

	if (heredoc_check(mini, 1) == 0)
	{
		tmp = open(".tmp", O_RDONLY);
		dup2(tmp, 0);
		close(tmp);
		not_builtin(mini, commands);
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
	{
		free_funct(mini->input_arr);
		return (free_funct(commands));
	}
	if (builtin == 1)
		command_handle(mini, exit_if_zero);
	else if (!exit_if_zero)
		piped_not_builtin(mini, commands);
	else
		run_non_bin(mini, commands);
	dup2(term_in, 0);
	dup2(term_out, 1);
	close(term_in);
	close(term_out);
	if (exit_if_zero == 0)
		exit (0);
	free_funct(commands);
	free_funct(mini->input_arr);
}

void	run_dup(int tmp_read, t_minihell *mini, t_data *data)
{
	if (tmp_read == -1)
		dup2(data->fd[1], STDOUT_FILENO);
	else if (data->next != NULL)
	{
		dup2(tmp_read, STDIN_FILENO);
		dup2(data->fd[1], STDOUT_FILENO);
	}
	else if (data->next == NULL)
		dup2(tmp_read, STDIN_FILENO);
	close(data->fd[1]);
	close(tmp_read);
	close(data->fd[0]);
	command(mini, data, 0);
}

void	close_pipe(int *tmp_read, t_data *data)
{
	close(data->fd[1]);
	if (*tmp_read != -1)
		close(*tmp_read);
	if (data->next != NULL)
	{
		*tmp_read = dup(STDIN_FILENO);
		*tmp_read = data->fd[0];
		close(data->fd[0]);
	}
	if (data->next == NULL)
		close(data->fd[0]);
}

void	run(t_minihell *mini, t_data *data)
{
	int	tmp_read;
	int	stat;

	if (mini->ll_len == 1)
	{
		command(mini, data, 1);
		return ;
	}
	tmp_read = -1;
	while (data != NULL)
	{
		data->fork = fork();
		if (data->fork == 0)
		{
			run_dup(tmp_read, mini, data);
			exit (0);
		}
		close_pipe(&tmp_read, data);
		data = data->next;
	}
	while (waitpid(-1, 0, 0) >= 0)
		;
}
