/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wting <wting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:28:24 by lwilliam          #+#    #+#             */
/*   Updated: 2023/02/23 21:34:09 by wting            ###   ########.fr       */
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

void	input_handle(t_minihell *mini)
{
	char	*t;
	char	*test;

	mini->yes = readline("\033[0;32mMinishell$ \033[0m");
	add_history(mini->yes);
	if (!mini->yes)
	{
		end(mini);
	}
	if (!check_open_quotes(mini->yes))
	{
		test = expand(mini->yes, mini);
		t = seperate(test, mini);
		mini->input_arr = lexer(test, mini);
		free(test);
	}
	else
	{	
		mini->input_arr = NULL;
		printf("syntax erriororororo\n");
	}
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

void	get_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 1024);
	printf("%s\n", pwd);
	free(pwd);
}

void	test(t_minihell *hell)
{
	char	*test[3];
	pid_t	pid;
	int		child_status;

	test[0] = "/bin/cat";
	test[1] = hell->input_arr[1];
	test[2] = hell->input_arr[2];
	pid = fork();
	if (pid == 0)
		execve(test[0], test, NULL);
	else
		waitpid(-1, NULL, 0);
	return ;
}

void	command_handle(t_minihell *mini)
{
	if (mini->input_arr && !ft_strncmp(mini->input_arr[0], "env", 4))
		print_env(mini->env_ll);
	else if (mini->input_arr && !ft_strncmp(mini->input_arr[0], "pwd", 4))
		get_pwd();
	else if (mini->input_arr && !ft_strncmp(mini->input_arr[0], "ls", 3))
		list_dir(mini);
	else if (mini->input_arr && !ft_strncmp(mini->input_arr[0], "cd", 3))
		change_dir(mini);
	else if (mini->input_arr && !ft_strncmp(mini->input_arr[0], "unset", 6))
		unset(mini);
	else if (mini->input_arr && !ft_strncmp(mini->input_arr[0], "export", 7))
		export(mini);
	else if (mini->input_arr && !ft_strncmp(mini->input_arr[0], "echo", 7))
		echo(mini);
	else if (mini->input_arr && !ft_strncmp(mini->input_arr[0], "exit", 5))
		end(mini);
	else if (mini->input_arr && !ft_strncmp(mini->input_arr[0], "cat", 4))
		test(mini);
	else if (mini->input_arr && mini->input_arr[0])
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
