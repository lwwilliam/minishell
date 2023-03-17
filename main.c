/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:28:24 by lwilliam          #+#    #+#             */
/*   Updated: 2023/03/17 21:38:16 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	esl(t_minihell *mini)
{
	char	*tmp;
	char	*tmp2;

	tmp = expand(mini->yes, mini);
	free(mini->yes);
	tmp2 = seperate(tmp);
	free(tmp);
	mini->input_arr = lexer(tmp2, mini);
	free(tmp2);
}

int	input_handle(t_minihell *mini)
{
	char	*tmp;
	char	*tmp2;

	mini->yes = readline("\033[0;32mMinishell$ \033[0m");
	add_history(mini->yes);
	if (!mini->yes)
		end(mini, 1);
	if (!check_valid(mini->yes))
		esl(mini);
	else
	{
		mini->input_arr = NULL;
		printf("Syntax error\n");
		free_funct(mini->input_arr);
		free(mini->yes);
		return (1);
	}
	dup_arr(mini->input_arr, mini);
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

// void	pr(t_data *d)
// {
// 	int x;

// 	x = 0;
// 	while (d != NULL)
// 	{
// 		printf("%d\n", x);
// 		for(int y = 0; d->cmd[y]; y++)
// 			printf("%s\n", d->cmd[y]);
// 		x++;
// 		d = d->next;
// 	}
// }

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
		// pr(mini.data);
		run(&mini);
		free_funct(mini.input_arr);
		clear_in(&mini.data);
	}
}
