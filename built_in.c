/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:10:42 by lwilliam          #+#    #+#             */
/*   Updated: 2023/04/13 15:49:09 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_num(char **in)
{
	int	x;

	x = 0;
	while (in[x++])
		;
	if (x > 2 && !ft_strncmp(in[0], "exit", 5))
		return (ft_atoi(in[1]));
	return (0);
}

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
		end(mini, 1, exit_num(mini->input_arr));
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

void	array_dup(t_minihell *mini)
{
	char	**dup;
	int		x;
	int		y;

	y = 0;
	x = 0;
	dup = mal_dup(mini);
	while (mini->input_arr[x])
	{
		if (!is_redir(mini->input_arr[x]))
			x += 2;
		else
			dup[y++] = ft_strdup(mini->input_arr[x++]);
	}
	x = -1;
	while (mini->input_arr[++x])
	{
		if (!is_redir(mini->input_arr[x]))
		{
			dup[y++] = ft_strdup(mini->input_arr[x++]);
			dup[y++] = ft_strdup(mini->input_arr[x]);
		}
	}
	free_funct(mini->input_arr);
	mini->input_arr = dup;
}
