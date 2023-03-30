/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wting <wting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:10:42 by lwilliam          #+#    #+#             */
/*   Updated: 2023/03/29 19:58:32 by wting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_handle(t_minihell *mini, int exit_if_zero)
{
	if (mini->input_arr && !ft_strncmp(mini->input_arr[0], "env", 4))
		print_env(mini->env_ll);
	else if (mini->input_arr && !ft_strncmp(mini->input_arr[0], "pwd", 4))
		get_pwd();
	else if (mini->input_arr && !ft_strncmp(mini->input_arr[0], "cd", 3))
		change_dir(mini);
	else if (mini->input_arr && !ft_strncmp(mini->input_arr[0], "unset", 6))
		unset(mini);
	else if (mini->input_arr && !ft_strncmp(mini->input_arr[0], "export", 7))
		export(mini);
	else if (mini->input_arr && !ft_strncmp(mini->input_arr[0], "echo", 7))
		echo(mini);
	else if (mini->input_arr && !ft_strncmp(mini->input_arr[0], "exit", 5) && \
		exit_if_zero == 0)
		exit(0);
	else if (mini->input_arr && !ft_strncmp(mini->input_arr[0], "exit", 5))
		end(mini, 1);
	else if (mini->input_arr && mini->input_arr[0])
		printf("Minishell: %s: command not found\n", mini->input_arr[0]);
}

int	builtin_check(t_minihell *mini)
{
	if (mini->input_arr && !ft_strncmp(mini->input_arr[0], "env", 4))
		return (1);
	else if (mini->input_arr && !ft_strncmp(mini->input_arr[0], "pwd", 4))
		return (1);
	else if (mini->input_arr && !ft_strncmp(mini->input_arr[0], "cd", 3))
		return (1);
	else if (mini->input_arr && !ft_strncmp(mini->input_arr[0], "unset", 6))
		return (1);
	else if (mini->input_arr && !ft_strncmp(mini->input_arr[0], "export", 7))
		return (1);
	else if (mini->input_arr && !ft_strncmp(mini->input_arr[0], "echo", 7))
		return (1);
	else if (mini->input_arr && !ft_strncmp(mini->input_arr[0], "exit", 5))
		return (1);
	return (0);
}
