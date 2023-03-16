/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:15:30 by lwilliam          #+#    #+#             */
/*   Updated: 2023/03/16 13:29:40 by lwilliam         ###   ########.fr       */
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
		if (!ft_strncmp(mini->input_arr[x], "<<", 3) && x == 0)
		{
			if (heredoc(mini, x) == 1)
				return (1);
		}
		if (!ft_strncmp(mini->input_arr[x], "<<", 3) && !mini->input_arr[x + 1])
		{
			printf("Minishell: syntax error near unexpected token `newline'\n");
			return (1);
		}
		else if (!ft_strncmp(mini->input_arr[x], "<<", 3) && test == 1)
			if (heredoc(mini, x) == 1)
				return (1);
		x++;
	}
	return (0);
}

int	heredoc(t_minihell *mini, int x)
{
	char	*key_word;
	char	*long_str;
	char	*long_str1;
	char	*here_arg;

	long_str = "";
	key_word = mini->input_arr[x + 1];
	while (1)
	{
		here_arg = readline("> ");
		if (!ft_strncmp(here_arg, key_word, ft_strlen(key_word) + 1))
		{
			if (ft_strlen(long_str) == 0)
				long_str = ft_calloc(1, sizeof(char));
			else
				long_str[ft_strlen(long_str)] = '\0';
			printf("%s", long_str);
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

// int	heredoc(t_minihell *mini, int x)
// {
// 	char	*here_arg;
// 	char	*long_str;
// 	char	*long_str1;
// 	char	*key_word;
// 	int		check_num;

// 	long_str = "";
// 	check_num = heredoc_check(mini);
// 	if (check_num == 2)
// 		return (1);
// 	while (check_num == 1)
// 	{
// 		here_arg = readline("> ");
// 		if (!ft_strncmp(here_arg, mini->input_arr[x + 1], 
// 			ft_strlen(mini->input_arr[x + 1]) + 1))
// 		{
// 			long_str[ft_strlen(long_str)] = '\0';
// 			printf("args:\n%s", long_str);
// 			free(here_arg);
// 			free(long_str);
// 			return (1);
// 		}
// 		long_str1 = strjoin_helper(long_str, here_arg, 0, 1);
// 		if (ft_strlen(long_str) > 0)
// 			free(long_str);
// 		long_str = strjoin_helper(long_str1, "\n", 1, 0);
// 	}
// 	return (0);
// }
