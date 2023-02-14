/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:00:03 by lwilliam          #+#    #+#             */
/*   Updated: 2023/02/14 21:20:40 by lwilliam         ###   ########.fr       */
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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_minihell
{
	char	**input_arr;
	t_env	*env_ll;
}	t_minihell;


//link_list for env stuff

//input handle (not done)
void	input_handle(t_minihell *mini);

//env handle
t_env	*env_init(t_minihell *mini, char **in);
void	print_env(t_env *env_ll, t_minihell *mini);
//returns the value from the env ll, what the value of the key is 
//e.g input = ("USER") output = lwilliam
char	*get_env(t_env *env_ll, char *what);

//directory
void	change_dir(t_minihell *mini);
//list diretory is not required
void	list_dir(t_minihell *mini);

//lexar
char	**lexer(char *str, t_minihell *mini);

//link_list
t_env	*list_create( char *key, char *value);
void	insert(t_env **link, t_env *newlist);

//free
void	free_funct(char **array);

#endif