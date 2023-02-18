/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:28:24 by lwilliam          #+#    #+#             */
/*   Updated: 2023/02/18 15:46:27 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_handle(t_minihell *mini)
{
	char	*t;
	char	*test;

	t = readline("\033[0;32mMinishell$ \033[0m");
	add_history(t);
	if (!t)
	{
		end(mini);
	}
	test = expand(t, mini);
	mini->input_arr = lexer(test, mini);
	free(test);
}

static void	signal_handler(int num)
{
	if (num == SIGINT)
	{
		write(0, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (num == SIGQUIT)
	{
		printf("\033[0;32mMinishell$ \033[0m");
		printf("%s", rl_line_buffer);
	}
}


void	sigquit_handler(int sig)
{
	(void)sig;
	printf("\b\b");
	signal(SIGQUIT, SIG_IGN);
	return ;
}

void	command_handle(t_minihell *mini)
{
	if (!ft_strncmp(mini->input_arr[0], "env", 4))
		print_env(mini->env_ll);
	else if (!ft_strncmp(mini->input_arr[0], "pwd", 4))
		printf("%s\n", getcwd(NULL, 1024));
	else if (!ft_strncmp(mini->input_arr[0], "ls", 3))
		list_dir(mini);
	else if (!ft_strncmp(mini->input_arr[0], "cd", 3))
		change_dir(mini);
	else if (!ft_strncmp(mini->input_arr[0], "unset", 6))
		unset(mini);
	else if (!ft_strncmp(mini->input_arr[0], "export", 7))
		export(mini);
	else if (!ft_strncmp(mini->input_arr[0], "echo", 7))
		echo(mini);
	else if (!ft_strncmp(mini->input_arr[0], "exit", 5))
		end(mini);
	else if (mini->input_arr[0])
		printf("Minishell: %s: command not found\n", mini->input_arr[0]);
}

int	main(int ac, char **av, char **envp)
{
	t_minihell		mini;
	struct termios	termios_new;

	(void)ac;
	(void)av;
	mini.env_ll = env_init(envp);
	tcgetattr(STDIN_FILENO, &termios_new);
	termios_new.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_new);
	tcsetattr(0, 0, &termios_new);
	while (1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		input_handle(&mini);
		command_handle(&mini);
		free_funct(mini.input_arr);
	}
}
