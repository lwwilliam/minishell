/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:15:30 by lwilliam          #+#    #+#             */
/*   Updated: 2023/03/03 18:26:44 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_check(t_minihell *mini)
{
	int	x;

	x = 0;
	while (mini->input_arr[x])
	{
		if (!ft_strncmp(mini->input_arr[x++], "<<", 3))
			return (1);
	}
	return (0);
}

int	heredoc(t_minihell *mini)
{
	char	*here_arg;

	while (heredoc_check(mini) == 1)
	{
		here_arg = readline("> ");
		if (!ft_strncmp(here_arg, mini->input_arr[1], ft_strlen(here_arg)))
		{
			
		}

	}
	return (0);
}
