/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:00:03 by lwilliam          #+#    #+#             */
/*   Updated: 2023/02/12 22:38:48 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <signal.h>
# include <termios.h>
# include <fcntl.h>
# include <dirent.h>

typedef struct s_minihell
{
	char	**env_arr;
	char	**input_arr;
}	t_minihell;

//input handle (not done)
void	input_handle(t_minihell *mini);

//env handle
int		env_init(char **in, t_minihell *mini);
void	print_env(char **env, t_minihell *mini);

//directory
void	what_dir(char *en, int print);
void	change_dir(t_minihell *mini);
void	list_dir(t_minihell *mini);

#endif