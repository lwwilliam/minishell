/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:00:03 by lwilliam          #+#    #+#             */
/*   Updated: 2023/02/17 19:37:39 by lwilliam         ###   ########.fr       */
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

# define VALID "not a valid identifier"

//link_list for env
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_minihell
{
	char	**input_arr;
	char	*yes;
	t_env	*env_ll;
}	t_minihell;

//input handle (not done)
void	input_handle(t_minihell *mini);

//env handle
t_env	*env_init(char **in);
void	print_env(t_env *env_ll);

//returns the value from the env_ll, what the value of the key is 
//e.g input = ("USER") output = lwilliam
char	*get_env(t_env *env_ll, char *what);

//directory
void	change_dir(t_minihell *mini);
void	assign_oldpwd(t_env *env_ll, char *old_pwd, t_minihell *mini);
//list diretory is not required
void	list_dir(t_minihell *mini);

//link_list
t_env	*list_create( char *key, char *value);
void	insert(t_env **link, t_env *newlist);
t_env	*add_node_end(t_env *head, char *key, char *value);
void	remove_node(t_env **head, char *key);
void	remove_head_node(t_env **head);

int		unset(t_minihell *mini);
int		export(t_minihell *mini);
int		check_exist(t_env *env_ll, char *key, char *value);

//echo
void	echo(t_minihell *mini);

//free
void	free_funct(char **array);

//lexer
char	**lexer(char *str, t_minihell *mini);
int		len_count(char *str);
int		word_count(char *str);
char	*find_env(char	*str, t_minihell *mini);
char	*strjoin_helper(char *str1, char *str2, int free1, int free2);
char	*expand(char *str, t_minihell *mini);
int		env_name_len(char *str, int bool);
char	*expand_helper(char *str, t_minihell *mini);

#endif