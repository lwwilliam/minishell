/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:19:44 by lwilliam          #+#    #+#             */
/*   Updated: 2023/02/23 16:33:24 by lwilliam         ###   ########.fr       */
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
			// printf("ld: (%s)\n", dir->d_name);
			if (!ft_strncmp(mini->input_arr[0], dir->d_name,
					ft_strlen(mini->input_arr[0]) + 1))
				return (1);
		}
		closedir(d);
	}
	return (2);
}

void	test(t_minihell *mini)
{
	char	**twodpath;
	char	*command;
	char	*test[5];
	pid_t	pid;
	int		x;

	x = 0;
	twodpath = ft_split(get_env(mini->env_ll, "PATH"), ':');
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
	test[0] = command;
	test[1] = mini->input_arr[1];
	test[2] = mini->input_arr[2];
	pid = fork();
	if (pid == 0)
	{
		if (execve(test[0], test, NULL) == -1)
		{
			printf("Minishell: %s: command not found\n", mini->input_arr[0]);
			end(mini);
			exit(0);
		}
	}
	else
		waitpid(-1, NULL, 0);
	free(command);
	free_funct(twodpath);
	return ;
}

