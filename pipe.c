/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wting <wting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:22:17 by lwilliam          #+#    #+#             */
/*   Updated: 2023/03/24 16:55:31 by wting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	write_error(char *string, char *argv)
// {
// 	while (string && *string)
// 		write(2, string++, 1);
// 	if (argv)
// 		while (*argv)
// 			write(2, argv++, 1);
// 	write(2, "\n", 1);
// 	return (1);
// }

// int	ft_exe(char **argv, int i, int temporary_file_descriptor)
// {
// 	argv[i] = NULL;
// 	dup2(temporary_file_descriptor, 0);
// 	close(temporary_file_descriptor);
// 	execve(argv[0], argv, NULL);
// 	return (write_error("error: cannot execute ", argv[0]));
// }

// void	piping(t_minihell *mini, int tmp_fd, int x)
// {
// 	int	fd[2];

// 	pipe(fd);
// 	if (fork() == 0)
// 	{
// 		dup2(fd[1], 1);
// 		if (ft_exe(mini->input_arr, x, tmp_fd))
// 			return ;
// 		close(fd[0]);
// 		close(fd[1]);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		close(tmp_fd);
// 		tmp_fd = fd[0];
// 	}
// }

// int	pipe_check(t_minihell *mini, int tmp_fd)
// {
// 	int	x;

// 	x = 0;
// 	while (mini->input_arr[x])
// 	{
// 		if (!ft_strncmp(mini->input_arr[x], "|", 2))
// 			piping(mini, tmp_fd, x);
// 		x++;
// 	}
// 	return (0);
// }

// else if(i != 0 && strcmp(argv[i], "|") == 0)
// {
// 	pipe(fd);
// 	if ( fork() == 0)
// 	{
		// dup2(fd[1], STDOUT_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		if (ft_exe(argv, i, temporary_file_descriptor, environment_variables))
// 			return (1);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		close(temporary_file_descriptor);
// 		temporary_file_descriptor = fd[0];
// 	}
// } 
