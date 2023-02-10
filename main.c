/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:28:24 by lwilliam          #+#    #+#             */
/*   Updated: 2023/02/10 21:16:41 by lwilliam         ###   ########.fr       */
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
	mini->input_arr = ft_split(t, ' ');
}

int	main(int ac, char **av, char **env)
{
	t_minihell	mini;

	(void)ac;
	(void)av;
	while (1)
	{
		input_handle(&mini);
		env_init(env, &mini);
		if (!ft_strncmp(mini.input_arr[0], "env", 3))
			print_env(env, &mini);
		else if (!ft_strncmp(mini.input_arr[0], "pwd", 3))
			printf("%s\n", getcwd(NULL, 1024));
		else if (!ft_strncmp(mini.input_arr[0], "ls", 2))
			list_dir(&mini);
		else if (!ft_strncmp(mini.input_arr[0], "cd", 2))
			change_dir(&mini);
		else if (!ft_strncmp(mini.input_arr[0], "exit", 4))
			return (69);
	}
}
