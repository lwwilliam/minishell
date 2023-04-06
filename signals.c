/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:52:42 by lwilliam          #+#    #+#             */
/*   Updated: 2023/04/06 18:56:22 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int num)
{
	if (num == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_handler2(int num)
{
	if (num == SIGINT)
		write(1, "\n", 1);
	if (num == SIGQUIT)
		write(1, "^\\Quit: 3\n", 10);
}

//if up == 0 \ down == 1 
void	signals(int up_down)
{
	if (up_down == 0)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (up_down == 1)
	{
		signal(SIGINT, signal_handler2);
		signal(SIGQUIT, signal_handler2);
	}
}
