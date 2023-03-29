/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wting <wting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:19:44 by lwilliam          #+#    #+#             */
/*   Updated: 2023/03/28 21:37:32 by wting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//returns 1 if is in the path else will return 0
int	list_dir(t_minihell *mini, char *path)
{
	DIR				*d;
	struct dirent	*dir;

	(void)mini;
	d = opendir(path);
	if (d)
	{
		while (1)
		{
			dir = readdir(d);
			if (dir == NULL)
				break ;
			if (!ft_strncmp(mini->input_arr[0], dir->d_name,
					ft_strlen(mini->input_arr[0]) + 1))
			{
				closedir(d);
				return (1);
			}
		}
		closedir(d);
	}
	return (2);
}

//2d array of path in $PATH
char	*path_array(t_minihell *mini, char *from_env)
{
	char	**twodpath;
	char	*command;
	int		x;

	x = 0;
	command = ft_strdup(mini->input_arr[0]);
	twodpath = ft_split(from_env, ':');
	while (twodpath[x])
	{
		if (list_dir(mini, twodpath[x]) == 1)
		{
			free(command);
			command = ft_strjoin(twodpath[x], "/");
			command = strjoin_helper(command, mini->input_arr[0], 1, 0);
			break ;
		}
		x++;
	}
	free_funct(twodpath);
	return (command);
}

char	**command_make(t_minihell *mini)
{
	char	**exec;
	char	*command;
	int		x;

	x = 0;
	while (mini->input_arr[x++])
		;
	command = path_array(mini, get_env(mini->env_ll, "PATH"));
	exec = ft_calloc(x, sizeof(char *));
	x = 0;
	exec[x] = ft_strdup(command);
	while (mini->input_arr[++x])
	{
		if (!ft_strncmp(mini->input_arr[x], ">", 2)
			|| !ft_strncmp(mini->input_arr[x], ">>", 3)
			|| !ft_strncmp(mini->input_arr[x], "<", 2)
			|| !ft_strncmp(mini->input_arr[x], "<<", 3))
			break ;
		exec[x] = ft_strdup(mini->input_arr[x]);
	}
	free(command);
	return (exec);
}

void	not_builtin(t_minihell *mini, char **commands, int exit_if_zero)
{
	char	**env;

	env = env_2d(mini->env_ll);
	mini->data->fork = fork();
	if (mini->data->fork == 0)
	{
		if (execve(commands[0], commands, env) == -1)
		{
			if (exit_if_zero == 0)
			{
				ft_putstr_fd("Minishell: ", 2);
				ft_putstr_fd(mini->input_arr[0], 2);
				ft_putstr_fd(": command not found\n", 2);
				exit(1);
			}
			printf("Minishell: %s: command not found\n", mini->input_arr[0]);
			end(mini, 0);
		}
	}
	else
		waitpid(mini->data->fork, NULL, 0);
	free_funct(env);
	unlink(".tmp");
	return ;
}
