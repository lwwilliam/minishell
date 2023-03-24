/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:15:30 by lwilliam          #+#    #+#             */
/*   Updated: 2023/03/24 20:20:32 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//if test == 1 : run heredoc
//if test == 0 : dont run heredoc unless the first input is << 
//e.g (<< t) 
int	heredoc_check(t_minihell *mini, int test)
{
	int	x;

	x = 0;
	while (mini->input_arr[x])
	{
		if (!ft_strncmp(mini->input_arr[x], "<<", 3) && !mini->input_arr[x + 1])
		{
			printf("Minishell: syntax error near unexpected token `newline'\n");
			return (1);
		}
		else if (!ft_strncmp(mini->input_arr[x], "<<", 3))
				heredoc(mini, x + 1);
		x++;
	}
	return (0);
}

void	heredoc_run(t_minihell *mini, char *str)
{
	int	tmp;

	(void)mini;
	tmp = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (ft_strlen(str) == 0)
		str = ft_calloc(1, sizeof(char));
	else
		str[ft_strlen(str)] = '\0';
	write(tmp, str, ft_strlen(str));
	close(tmp);
	free(str);
}

int	heredoc(t_minihell *mini, int x)
{
	char	*key_word;
	char	*long_str;
	char	*long_str1;
	char	*here_arg;

	long_str = "";
	key_word = mini->input_arr[x];
	while (1)
	{
		here_arg = readline("> ");
		if (!ft_strncmp(here_arg, key_word, ft_strlen(key_word) + 1))
		{
			heredoc_run(mini, long_str);
			free(here_arg);
			if (x == 0)
				return (1);
			else
				return (0);
		}
		long_str1 = strjoin_helper(long_str, here_arg, 0, 1);
		if (ft_strlen(long_str) > 0)
			free(long_str);
		long_str = strjoin_helper(long_str1, "\n", 1, 0);
	}
	return (0);
}
