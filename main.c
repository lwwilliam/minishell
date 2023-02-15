/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wting <wting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:28:24 by lwilliam          #+#    #+#             */
/*   Updated: 2023/02/15 21:50:52 by wting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_init(char **in, t_minihell *mini)
{
	int	x;

	x = 0;
	while (in[x])
		x++;
	mini->env_arr = (char **)ft_calloc(x + 1, sizeof(char *));
	mini->env_arr[x] = NULL;
	x = -1;
	while (in[++x])
		mini->env_arr[x] = ft_strdup(in[x]);
	return (0);
}

void	print_env(char **env, t_minihell *mini)
{
	int	x;

	env_init(env, mini);
	x = 0;
	while (mini->env_arr[x])
		printf("%s\n", mini->env_arr[x++]);
}

void	input_handle(t_minihell *mini)
{
	char	*t;

	t = readline("\033[0;32mMinishell$ \033[0m");
	add_history(t);
	if (!t)
	{
		exit(1);
	}
	printf("t: %s\n", t);
	char *test = expand(t, mini);
	printf("str :%s\n", test);
	free (test);
}

void	sigint_handler(int sig)
{
	(void)sig;
	printf("\b\b");
	printf("int called\n");
	return ;
}

void	sigquit_handler(int sig)
{
	(void)sig;
	printf("\b\b");
	printf("quit called");
	return ;
}

// void	tmp_env(t_minihell *mini)
// {
// 	char *arg[] = {"ls", NULL};
// 	execve("/bin/ls", arg, NULL);
// }

int	main(int ac, char **av, char **env)
{
	t_minihell	mini;

	(void)ac;
	(void)av;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	while (1)
	{
		env_init(env, &mini);
		input_handle(&mini);
		// printf("%s\n", mini.input_arr[0]);
		// printf("%s\n", mini.input_arr[1]);
		// if (!ft_strncmp(mini.input_arr[0], "env", 3))
		// 	print_env(env, &mini);
		// else if (!ft_strncmp(mini.input_arr[0], "pwd", 3))
		// 	printf("%s\n", getcwd(NULL, 1024));
		// else if (!ft_strncmp(mini.input_arr[0], "ls", 2))
		// 	list_dir(&mini);
		// else if (!ft_strncmp(mini.input_arr[0], "cd", 2))
		// 	change_dir(&mini);
		// if (!ft_strncmp(mini.input_arr[0], "exit", 4))
		// 	return (69);
	}
}
