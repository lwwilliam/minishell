/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:28:24 by lwilliam          #+#    #+#             */
/*   Updated: 2023/02/16 18:56:22 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_handle(t_minihell *mini)
{
	char	*t;

	t = readline("\033[0;32mMinishell$ \033[0m");
	add_history(t);
	if (!t)
	{
		exit(1);
	}
	mini->input_arr = ft_split(t, ' ');
}

void	sigint_handler(int sig)
{
	(void)sig;
	printf("\b\b");
	printf("\033[0;32mMinishell$ \033[0m\n");
}

void	sigquit_handler(int sig)
{
	(void)sig;
	printf("\b\b");
	printf("quit called");
	return ;
}

int	main(int ac, char **av, char **envp)
{
	t_minihell	mini;

	(void)ac;
	(void)av;
	mini.env_ll = env_init(envp);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	while (1)
	{
		input_handle(&mini);
		if (!ft_strncmp(mini.input_arr[0], "env", 4))
			print_env(mini.env_ll);
		else if (!ft_strncmp(mini.input_arr[0], "pwd", 4))
			printf("%s\n", getcwd(NULL, 1024));
		else if (!ft_strncmp(mini.input_arr[0], "ls", 3))
			list_dir(&mini);
		else if (!ft_strncmp(mini.input_arr[0], "cd", 3))
			change_dir(&mini);
		else if (!ft_strncmp(mini.input_arr[0], "unset", 6))
			unset(&mini);
		else if (!ft_strncmp(mini.input_arr[0], "export", 7))
			export(&mini);
		else if (!ft_strncmp(mini.input_arr[0], "exit", 5))
			return (69);
	}
}
