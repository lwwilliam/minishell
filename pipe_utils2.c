/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wting <wting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:10:34 by wting             #+#    #+#             */
/*   Updated: 2023/04/18 15:58:05 by wting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_no_pipes(t_minihell *mini, t_data *data)
{
	if (mini->ll_len == 1)
	{
		mini->input_arr = arr_dup(data->cmd);
		run_heredoc(mini, data);
		if (command_check(mini) != 0)
			printf("Minishell: %s: command not found.\n", mini->input_arr[0]);
		free_funct(mini->input_arr);
		command(mini, data, 1);
		term_reset(data);
		return (0);
	}
	return (1);
}

int	command_check(t_minihell *mini)
{
	char	*path;

	if (builtin_check(mini))
		return (0);
	path = path_array(mini, get_env(mini->env_ll, "PATH"));
	if (access(path, X_OK) == 0)
	{
		free(path);
		return (0);
	}
	else
	{
		free(path);
		return (1);
	}
}

void	pre_fork(t_minihell *mini, t_data *data)
{
	mini->input_arr = arr_dup(data->cmd);
	run_heredoc(mini, data);
	if (command_check(mini) != 0)
		printf("Minishell: %s: command not found.\n", mini->input_arr[0]);
	free_funct(mini->input_arr);
}
