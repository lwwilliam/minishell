/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:19:44 by lwilliam          #+#    #+#             */
/*   Updated: 2023/02/23 21:40:26 by lwilliam         ###   ########.fr       */
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
	command = NULL;
	twodpath = ft_split(from_env, ':');
	while (twodpath[x])
	{
		if (list_dir(mini, twodpath[x]) == 1)
		{
			command = ft_strjoin(twodpath[x], "/");
			command = strjoin_helper(command, mini->input_arr[0], 1, 0);
			break ;
		}
		x++;
	}
	free_funct(twodpath);
	return (command);
}

void	not_builtin(t_minihell *mini)
{
	char	*command;
	char	*exec[5];
	pid_t	pid;

	command = path_array(mini, get_env(mini->env_ll, "PATH"));
	exec[0] = command;
	exec[1] = mini->input_arr[1];
	exec[2] = mini->input_arr[2];
	exec[3] = mini->input_arr[3];
	pid = fork();
	if (pid == 0)
	{
		if (execve(exec[0], exec, NULL) == -1)
		{
			printf("Minishell: %s: command not found\n", mini->input_arr[0]);
			free(command);
			end(mini, 0);
		}
	}
	else
		waitpid(-1, NULL, 0);
	free(command);
	return ;
}

