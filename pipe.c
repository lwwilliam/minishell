/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wting <wting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:22:17 by lwilliam          #+#    #+#             */
/*   Updated: 2023/04/13 15:07:24 by wting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(int fd)
{
	dprintf(2, "pipe_closed: %d\n", fd);
	if (close(fd) == -1)
		dprintf(2, "CLOSE ERROR\n");
}

void	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		dprintf(2, "dup2 ERROR\n");
}

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
		ft_close(tmp);
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

	// term_in = dup(STDIN_FILENO);
	// term_out = dup(STDOUT_FILENO);
	mini->input_arr = arr_dup(data->cmd);
	builtin = builtin_check(mini);
	commands = command_make(mini);
	// if (redirect_check(mini, commands[0]) == 1)
	// 	return (free_funct(commands));
	// if (builtin == 1)
	// 	command_handle(mini, exit_if_zero);
	// else if (!exit_if_zero)
	piped_not_builtin(mini, commands);
	// else
	// 	run_non_bin(mini, commands);
	// dup2(term_in, 0);
	// dup2(term_out, 1);
	// ft_close(term_in);
	// ft_close(term_out);
	if (exit_if_zero == 0)
		exit (0);
	free_funct(commands);
	free_funct(mini->input_arr);
}

void	close_all_pipes(t_data *data)
{
	while (data != NULL)
	{
		ft_close(data->fd[0]);
		ft_close(data->fd[1]);
		data = data->next;
	}
}

void	run_dup(int *tmp_read, t_minihell *mini, t_data *data, t_data *first)
{
	t_data	*tmp;

	if (*tmp_read == -2)
		ft_dup2(data->fd[1], STDOUT_FILENO);
	else if (data->next != NULL)
	{
		ft_dup2(*tmp_read, STDIN_FILENO);
		ft_dup2(data->fd[1], STDOUT_FILENO);
	}
	else
		ft_dup2(*tmp_read, STDIN_FILENO);
	close_all_pipes(first);
	command(mini, data, 0);
}

void	run_pipes(t_minihell *mini, t_data *data, t_data *first)
{
	int	tmp_read;

	tmp_read = -2;
	while (data != NULL)
	{
		data->fork = fork();
		if (data->fork == 0)
			run_dup(&tmp_read, mini, data, first);
		else if (data->fork == -1)
		{
			ft_putstr_fd("Fork failed\n", 2);
			exit (1);
		}
		else
		{
			waitpid(0, 0, -1);
			if (data->next != NULL)
				tmp_read = data->fd[0];
		}
		data = data->next;
	}
}

void	run(t_minihell *mini, t_data *data)
{
	int		tmp_read;
	int		stat;
	t_data	*head;
	t_data	*first;

	if (mini->ll_len == 1)
	{
		command(mini, data, 1);
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
