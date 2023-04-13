/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:00:03 by lwilliam          #+#    #+#             */
/*   Updated: 2023/04/13 17:34:08 by lwilliam         ###   ########.fr       */
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
# include <sys/types.h> 
# include <sys/wait.h> 

# define REDIR_ERR "Minishell: syntax error near unexpected taken 'newline\n"

int	g_err_code;

//link_list for env
typedef struct s_env
{
	char			*key;
	char			*value;
	int				print;
	struct s_env	*next;
}	t_env;
//if print == 0 then print

typedef struct s_data
{
	char			**cmd;
	int				fd[2];
	int				is_last_node;
	int				term_in;
	int				term_out;
	pid_t			fork;
	pid_t			split;
	struct s_data	*next;
}	t_data;

typedef struct s_minihell
{
	char			**input_arr;
	char			**term_in;
	char			*yes;
	char			*tmp;
	int				ll_len;
	t_env			*env_ll;
	t_data			*data;
	struct termios	termios_old;
	struct termios	termios_new;
}	t_minihell;

void	term(t_minihell *mini);

//built_in
void	command_handle(t_minihell *mini, int exit_if_zero);
int		builtin_check(t_minihell *mini);

//input handle (not done)
int		input_handle(t_minihell *mini);

//env handle
t_env	*env_init(char **in);
void	print_env(t_env *env_ll);

//returns the value from the env_ll, what the value of the key is 
//e.g input = ("USER") output = lwilliam
char	*get_env(t_env *env_ll, char *what);

//directory
void	change_dir(t_minihell *mini);
void	assign_oldpwd(t_env *env_ll, char *old_pwd, t_minihell *mini);
void	pwd_update(t_env *env_ll, char *new_pwd, t_minihell *mini);

void	get_pwd(void);

//link_list
t_env	*list_create( char *key, char *value);
void	insert(t_env **link, t_env *newlist);
t_env	*add_node_end(t_env *head, char *key, char *value, int print);
void	remove_node(t_env **head, char *key);
void	remove_head_node(t_env **head);

int		unset(t_minihell *mini);
int		export(t_minihell *mini);
int		export_error(char *in, char *key, char *value);
int		check_exist(t_env *env_ll, char *key, char *value, int yes_no);
// int		check_exist(t_env *env_ll, char *key, char *value, int yes_no);

//echo
void	echo(t_minihell *mini);

//signals
void	signals(int up_down);

//free
void	free_funct(char **array);
void	freelist(t_env **env);
void	end(t_minihell *mini, int print, int num);

//lexer
char	**lexer(char *str, t_minihell *mini);
int		key_len(char *str);
int		len_count(char *str);
int		word_count(char *str);
char	*strjoin_helper(char *str1, char *str2, int free1, int free2);
char	*expand(char *str, t_minihell *mini);
int		env_name_len(char *str, int bool);
char	*expand_helper(char *str, t_minihell *mini);
void	esl(t_minihell *mini);

//list diretory is not required
void	not_builtin(t_minihell *mini, char **commands);
char	**command_make(t_minihell *mini);

// void	reading(t_minihell *mini);
int		heredoc(t_minihell *mini, int x);
int		heredoc_check(t_minihell *mini);

//env linked list to 2d array
char	**env_2d(t_env *env);

//redirections
int		redirect_check(t_minihell *mini, char *valid);
// "<"
int		left_redirect(t_minihell *mini, int x, char *valid);
//">"
int		right_redirect(t_minihell *mini, int x, char *valid);
// ">>"
int		right_append(t_minihell *mini, int x, char *valid);

void	array_dup(t_minihell *mini);
char	**mal_dup(t_minihell *mini);
int		is_redir(char *str);

//pipe
void	run(t_minihell *mini, t_data *data);
void	run_bin(t_minihell *mini, char **commands, int exit_if_zero);
void	piped_not_builtin(t_minihell *mini, char **commands);
char	**arr_dup(char **dup);
void	close_all_pipes(t_data *data);
void	term_reset(t_data *data);

//seperate
int		count_spaces(char *str);
char	*seperate(char *str);
int		find_set(char c);

//error handling
int		check_valid(char *str);
int		check_open_quotes(char *str);

//input linked list functions
t_data	*lcreate( char **cmd);
void	input_init(t_data **head, t_data *newnode);
void	clear_in(t_data **data);
char	**assign(int len, int x, char **command, t_minihell *mini);
void	dup_arr(char **command, t_minihell *mini);

#endif