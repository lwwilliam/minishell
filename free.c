/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:23:59 by lwilliam          #+#    #+#             */
/*   Updated: 2023/04/18 14:56:27 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_funct(char **array)
{
	char	**tmp;

	tmp = array;
	while (tmp && *tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(array);
}

void	freelist(t_env **env)
{
	t_env	*current;
	t_env	*next;

	current = *env;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free (current);
		current = next;
	}
	*env = NULL;
}

void	end(t_minihell *mini, int print, int num)
{
	rl_clear_history();
	freelist(&mini->env_ll);
	if (print == 1)
	{
		printf("exit\n");
	}
	tcsetattr(0, 0, &mini->termios_old);
	exit(num);
}

int	export_error(char *in, char *key, char *value)
{
	int	x;

	x = 0;
	if (!ft_strchr(key, '_'))
	{
		g_err_code = 1;
		printf("Minishell: export: '%s': not a valid identifier\n", in);
		free(value);
		free(key);
	}
	else if (in[1] != '=')
	{
		free(key);
		free(value);
	}
	return (1);
}

void	term(t_minihell *mini)
{
	tcgetattr(STDIN_FILENO, &mini->termios_new);
	tcgetattr(STDIN_FILENO, &mini->termios_old);
	mini->termios_new.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &mini->termios_new);
	tcsetattr(0, 0, &mini->termios_new);
}
