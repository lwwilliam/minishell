/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:15:30 by lwilliam          #+#    #+#             */
/*   Updated: 2023/03/09 18:28:56 by lwilliam         ###   ########.fr       */
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
	char	*long_str;
	char	*long_str1;

	long_str = "";
	while (heredoc_check(mini) == 1 && mini->input_arr[1])
	{
		here_arg = readline("> ");
		if (!ft_strncmp(here_arg, mini->input_arr[1], ft_strlen(here_arg)))
		{
			long_str[ft_strlen(long_str)] = '\0';
			printf("args:\n%s", long_str);
			free(here_arg);
			free(long_str);
			return (1);
		}
		long_str1 = strjoin_helper(long_str, here_arg, 0, 1);
		if (ft_strlen(long_str) > 0)
			free(long_str);
		long_str = strjoin_helper(long_str1, "\n", 1, 0);
	}
	return (0);
}
