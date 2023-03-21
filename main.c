/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:28:24 by lwilliam          #+#    #+#             */
/*   Updated: 2023/03/22 00:30:03 by lwilliam         ###   ########.fr       */
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
	mini->term_in = lexer(tmp2, mini);
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
		mini->term_in = NULL;
		printf("Syntax error\n");
		free_funct(mini->term_in);
		free(mini->yes);
		return (1);
	}
	dup_arr(mini->term_in, mini);
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

void	run(t_minihell *mini, t_data *data)
{
	int		builtin;
	int		term_in;
	int		term_out;
	char	**commands;

	term_in = dup(0);
	term_out = dup(1);
	while (data != NULL)
	{
		mini->input_arr = data->cmd;
		builtin = builtin_check(mini);
		commands = command_make(mini);
		redirect_check(mini, commands[0]);
		if (builtin == 1)
			command_handle(mini);
		else
		{
			if (heredoc_check(mini, 0) == 0)
				not_builtin(mini, commands);
		}
		free_funct(commands);
		data = data->next;
	}
	dup2(term_in, 0);
	dup2(term_out, 1);
	close(term_in);
	close(term_out);
}

void	pr(t_data *d)
{
	int x;

	x = 0;
	while (d != NULL)
	{
		printf("%d\n", d->fd[0]);
		printf("%d\n", d->fd[1]);
		for(int y = 0; d->cmd[y]; y++)
			printf("%s\n", d->cmd[y]);
		x++;
		d = d->next;
	}
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
		if (mini.term_in[0] == 0)
		{
			free_funct(mini.term_in);
			continue ;
		}
		pr(mini.data);
		run(&mini, mini.data);
		free_funct(mini.term_in);
		clear_in(&mini.data);
	}
}
