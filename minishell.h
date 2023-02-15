/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wting <wting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:00:03 by lwilliam          #+#    #+#             */
/*   Updated: 2023/02/15 21:05:59 by wting            ###   ########.fr       */
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


// struct s_struct
// {
// 	char	*str;
// 	int		type;
// };

// struct s_struct	*new_struct(char *str, int type)
// {
// 	struct s_struct	*ptr;

// 	ptr = malloc(sizeof(struct s_struct));
// 	ptr->str = str;
// 	ptr->type = type;
// 	return (ptr);
// }

// void	ft_lst(void)
// {
// 	t_list	*lst;

// 	lst = NULL;
// 	ft_lstadd_back(&lst, ft_lstnew(new_struct("Hatsune Miku", 831)));
// }

//input handle (not done)
void	input_handle(t_minihell *mini);

//env handle
int		env_init(char **in, t_minihell *mini);
void	print_env(char **env, t_minihell *mini);

//directory
void	what_dir(char *en, int print);
void	change_dir(t_minihell *mini);
void	list_dir(t_minihell *mini);

//lexer
char	**lexer(char *str, t_minihell *mini);
int		len_count(char *str);
int		word_count(char *str);
char	*find_env(char	*str, t_minihell *mini);
char	*strjoin_helper(char *str1, char *str2, int free1, int free2);
char	*expand(char *str, t_minihell *mini);

#endif