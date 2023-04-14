/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:31:15 by lwilliam          #+#    #+#             */
/*   Updated: 2023/04/14 18:37:37 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	term_reset(t_data *data)
{
	dup2(data->term_in, 0);
	dup2(data->term_out, 1);
	close(data->term_in);
	close(data->term_out);
}

void	close_all_pipes(t_data *data)
{
	while (data != NULL)
	{
		close(data->fd[0]);
		close(data->fd[1]);
		data = data->next;
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

void	piped_not_builtin(t_minihell *mini, char **commands)
{
	char	**env;

	env = env_2d(mini->env_ll);
	execve(commands[0], commands, env);
	exit(127);
}

void	run_bin(t_minihell *mini, char **commands, int exit_if_zero)
{
	if (!exit_if_zero)
		piped_not_builtin(mini, commands);
	else
		not_builtin(mini, commands);
}
