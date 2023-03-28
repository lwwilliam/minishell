/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wting <wting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:28:24 by lwilliam          #+#    #+#             */
/*   Updated: 2023/03/28 21:19:22 by wting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lstsize(t_data *lst)
{
	int	x;

	x = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		lst = lst->next;
		x++;
	}
	return (x);
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
	mini->ll_len = lstsize(mini->data);
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

// void	pr(t_data *d)
// {
// 	int	x;

// 	x = 0;
// 	while (d != NULL)
// 	{
// 		printf("%d\n", d->fd[0]);
// 		printf("%d\n", d->fd[1]);
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
		if (mini.term_in[0] == 0)
		{
			free_funct(mini.term_in);
			continue ;
		}
		// pr(mini.data);
		run(&mini, mini.data);
		free_funct(mini.term_in);
		clear_in(&mini.data);
	}
}
