/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:15:30 by lwilliam          #+#    #+#             */
/*   Updated: 2023/03/07 17:44:49 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_check(t_minihell *mini)
{
	int	x;

	x = 0;
	while (mini->input_arr[x])
	{
		if (!ft_strncmp(mini->input_arr[x++], "<<", 3))
			return (1);
	}
	return (0);
}

int	heredoc(t_minihell *mini)
{
	char	*here_arg;
	char	*long_str;
	char	*long_str1;

	long_str = "";
	while (heredoc_check(mini) == 1 && mini->input_arr[1])
	{
		here_arg = readline("> ");
		if (!ft_strncmp(here_arg, mini->input_arr[1], ft_strlen(here_arg)))
		{
			long_str[ft_strlen(long_str)] = '\0';
			printf("args:\n%s", long_str);
			free(here_arg);
			free(long_str);
			return (1);
		}
		long_str1 = strjoin_helper(long_str, here_arg, 0, 1);
		if (ft_strlen(long_str) > 0)
			free(long_str);
		long_str = strjoin_helper(long_str1, "\n", 1, 0);
	}
	redirect_check(mini);
	return (0);
}

int	redirect_check(t_minihell *mini)
{
	int	x;

	x = 0;
	while (mini->input_arr[x])
	{
		if (!ft_strncmp(mini->input_arr[x], ">", 2))
			right_redirect(mini, x);
		else if (!ft_strncmp(mini->input_arr[x], ">>", 3))
			right_append(mini, x);
		x++;
	}
	return (0);
}

void	right_redirect(t_minihell *mini, int x)
{
	int		fd;
	char	*tmp_msg;

	tmp_msg = ft_strdup(mini->input_arr[0]);
	fd = open(mini->input_arr[x + 1], O_CREAT | O_WRONLY, 0644);
	if (fd < 0)
	{
		printf("error\n");
		return ;
	}
	write(fd, tmp_msg, ft_strlen(tmp_msg));
	close(fd);
	return ;
}

void	right_append(t_minihell *mini, int x)
{
	int		fd;
	char	*tmp_msg;

	tmp_msg = ft_strdup(mini->input_arr[0]);
	fd = open(mini->input_arr[x + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		printf("error\n");
		return ;
	}
	write(fd, tmp_msg, ft_strlen(tmp_msg));
	close(fd);
	return ;
}

// int	ft_exe(char **argv, int i, int tmp_fd, char **environment_variables)
// {
// 	argv[i] = NULL;
// 	dup2(tmp_fd, STDIN_FILENO);
// 	close(tmp_fd);
// 	execve(argv[0], argv, environment_variables);
// 	return (0);
// }

// void	test(t_minihell *mini, char **env)
// {
// 	int	tmp_fd;
// 	int	fd[2];
// 	int	i;

// 	tmp_fd = dup(STDIN_FILENO);
// 	i = pipe_check(mini);
// 	if (i > 0)
// 	{
// 		printf("piping\n");
// 		pipe(fd);
// 		if (fork() == 0)
// 		{
// 			dup2(fd[1], STDOUT_FILENO);
// 			close(fd[0]);
// 			close(fd[1]);
// 			if (ft_exe(mini->input_arr, i, tmp_fd, env))
// 			{
// 				printf("message: 1\n");
// 				return ;
// 			}
// 		}
// 		else
// 		{
// 			close(fd[1]);
// 			close(tmp_fd);
// 			tmp_fd = fd[0];
// 		}
// 	}
// 	return ;
// }
