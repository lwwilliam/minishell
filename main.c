/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:28:24 by lwilliam          #+#    #+#             */
/*   Updated: 2023/02/09 22:19:59 by lwilliam         ###   ########.fr       */
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


int	main(int ac, char **av, char **env)
{
	t_minihell	mini;
	char		*t;
	char		*pwd;
	int			x;

	(void)ac;
	(void)av;
	env_init(env, &mini);
	while (1)
	{
		printf("%s", "Minishell : ");
		t = readline(0);
		printf("%s\n", t);
		if (!ft_strncmp(t, "env", 3))
		{
			x = 0;
			while (mini.env_arr[x])
				printf("%s\n", mini.env_arr[x++]);
		}
		if (!ft_strncmp(t, "pwd", 3))
			printf("%s\n", getcwd(NULL, 1024));
		if (!ft_strncmp(t, "exit", 4))
			return (69);
	}
}
