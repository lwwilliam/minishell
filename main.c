/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:28:24 by lwilliam          #+#    #+#             */
/*   Updated: 2023/02/09 21:33:07 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_init(char **in, t_minihell *mini)
{
	int	x;

	x = 0;
	mini = (t_minihell *)malloc(sizeof(t_minihell));
	while (in[x])
		x++;
	mini->env_arr = malloc(sizeof(char *) * (x + 1));
	mini->env_arr[x] = NULL;
	while (--x >= 0)
		mini->env_arr[x] = ft_strdup(in[x]);
	return (0);
}


int	main(int ac, char **av, char **env)
{
	t_minihell	mini;
	char		*t;
	char		*pwd;
	int			x;

	(void)ac;
	(void)av;
	env_init(env, &mini);
	// pwd = getcwd(NULL, 1024);
	while (1)
	{
		printf("%s", "Minishell : ");
		t = readline(0);
		printf("%s\n", t);
		// if (!ft_strncmp(t, "env", 3))
		// {
		// 	x = 0;
		// 	while (mini.env_arr[x++])
		// 		printf("%s\n", mini.env_arr[x]);
		// }
		if (!ft_strncmp(t, "exit", 4))
			return (69);
	}
}
