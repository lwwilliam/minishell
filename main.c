/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:28:24 by lwilliam          #+#    #+#             */
/*   Updated: 2023/03/01 18:34:13 by lwilliam         ###   ########.fr       */
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
	char	*test;

	mini->yes = readline("\033[0;32mMinishell$ \033[0m");
	add_history(mini->yes);
	if (!mini->yes)
		end(mini, 1);
	if (!check_open_quotes(mini->yes))
	{
		test = expand(mini->yes, mini);
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

int	main(int ac, char **av, char **envp)
{
	t_minihell		mini;
	int				builtin;

	(void)ac;
	(void)av;
	builtin = 0;
	mini.env_ll = env_init(envp);
	term();
	while (1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		input_handle(&mini);
		if (mini.input_arr[0] == 0)
		{
			free_funct(mini.input_arr);
			continue ;
		}
		builtin = builtin_check(&mini);
		if (builtin == 1)
			command_handle(&mini);
		else
			not_builtin(&mini);
		free_funct(mini.input_arr);
	}
}
