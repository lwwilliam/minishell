/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:28:24 by lwilliam          #+#    #+#             */
/*   Updated: 2023/03/16 18:10:53 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_open_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			while (str[++i] != '\'')
				if (!str[i])
					return (1);
		if (str[i] == '"')
			while (str[++i] != '"')
				if (!str[i])
					return (1);
		++i;
	}
	return (0);
}

int	input_handle(t_minihell *mini)
{
	char	*tmp;
	char	*tmp2;

	mini->yes = readline("\033[0;32mMinishell$ \033[0m");
	add_history(mini->yes);
	if (!mini->yes)
		end(mini, 1);
	if (!check_open_quotes(mini->yes))
	{
		tmp = expand(mini->yes, mini);
		free(mini->yes);
		tmp2 = seperate(tmp);
		free(tmp);
		mini->input_arr = lexer(tmp2, mini);
		free(tmp2);
	}
	else
	{
		mini->input_arr = NULL;
		printf("Syntax error\n");
		free_funct(mini->input_arr);
		free(mini->yes);
		return (1);
	}
	return (0);
}

void	signal_handler(int num)
{
	if (num == SIGINT)
	{
		write(0, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	run(t_minihell *mini)
{
	int		builtin;
	int		fd_in;
	int		fd_out;
	char	**commands;

	builtin = builtin_check(mini);
	fd_in = dup(1);
	fd_out = dup(0);

	commands = command_make(mini);
	redirect_check(mini, commands[0]);
	// char	*test[3];
	// test[0] = "/bin/ls";
	// test[1] = "directory.c";
	// test[1] = NULL;
	// if (fork() == 0)
	// 	execve(test[0], test, NULL);
	// else
	// 	waitpid(-1, NULL, 0);
	// pipe_check(mini, saved_fd);
	// close(saved_fd);
	if (builtin == 1)
		command_handle(mini);
	else
	{
		if (heredoc_check(mini, 0) == 0)
			not_builtin(mini, commands);
	}
	dup2(fd_in, 1);
	dup2(fd_out, 0);
	close(fd_in);
	close(fd_out);
	free_funct(commands);
}

int	main(int ac, char **av, char **envp)
{
	t_minihell		mini;

	(void)ac;
	(void)av;
	mini.env_ll = env_init(envp);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	term();
	while (1)
	{
		if (input_handle(&mini) == 1)
			continue ;
		if (mini.input_arr[0] == 0)
		{
			free_funct(mini.input_arr);
			continue ;
		}
		run(&mini);
		free_funct(mini.input_arr);
	}
}
