/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:28:24 by lwilliam          #+#    #+#             */
/*   Updated: 2023/04/13 18:38:59 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lstsize(t_data *lst)
{
	int	x;

	x = 0;
	if (!lst)
		return (1);
	while (lst)
	{
		lst = lst->next;
		x++;
	}
	return (x);
}

int	input_handle(t_minihell *mini)
{
	mini->yes = readline("\033[0;32mMinishell$ \033[0m");
	if (!mini->yes)
		end(mini, 1, 0);
	if (ft_strncmp(mini->yes, "", 2))
		add_history(mini->yes);
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
	term(&mini);
	while (1)
	{
		signals(0);
		if (input_handle(&mini) == 1)
			continue ;
		if (mini.term_in[0] == 0)
		{
			free_funct(mini.term_in);
			continue ;
		}
		mini.ll_len = lstsize(mini.data);
		g_err_code = 0;
		tcsetattr(0, 0, &mini.termios_old);
		signals(1);
		run(&mini, mini.data);
		tcsetattr(0, 0, &mini.termios_new);
		free_funct(mini.term_in);
		clear_in(&mini.data);
	}
}
