/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:19:44 by lwilliam          #+#    #+#             */
/*   Updated: 2023/03/10 23:52:59 by lwilliam         ###   ########.fr       */
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
	int		row;

	x = 0;
	row = 0;
	while (mini->input_arr[row++])
		;
	command = path_array(mini, get_env(mini->env_ll, "PATH"));
	exec = malloc(sizeof(char *) * row);
	exec[x] = ft_substr(command, 0, ft_strlen(command));
	while (mini->input_arr[++x])
	{
		if (!ft_strncmp(mini->input_arr[x], ">", 2)
			|| !ft_strncmp(mini->input_arr[x], ">>", 3)
			|| !ft_strncmp(mini->input_arr[x], "<<", 3))
			break ;
		exec[x] = ft_substr(mini->input_arr[x], 0,
				ft_strlen(mini->input_arr[x]));
	}
	exec[x] = NULL;
	free(command);
	return (exec);
}

void	not_builtin(t_minihell *mini)
{
	char	**commands;
	pid_t	pid;
	char	**env;

	env = env_2d(mini->env_ll);
	commands = command_make(mini);
	pid = fork();
	if (pid == 0)
	{
		redirect_check(mini);
		if (execve(commands[0], commands, env) == -1)
		{
			printf("Minishell: %s: command not found\n", mini->input_arr[0]);
			end(mini, 0);
		}
	}
	else
	{
		waitpid(-1, NULL, 0);
	}
	free_funct(commands);
	free_funct(env);
	return ;
}
