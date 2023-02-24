/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:23:59 by lwilliam          #+#    #+#             */
/*   Updated: 2023/02/24 14:05:06 by lwilliam         ###   ########.fr       */
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

void	end(t_minihell *mini, int print)
{
	rl_clear_history();
	freelist(&mini->env_ll);
	if (print == 1)
	{
		printf("exit\n");
		system("leaks Minishell");
	}
	exit(0);
}

int	export_error(char *in, char *key, char *value)
{
	printf("Minishell: export: '%s': not a valid identifier\n", in);
	free(value);
	free(key);
	return (1);
}

void	term(void)
{
	struct termios	termios_new;

	tcgetattr(STDIN_FILENO, &termios_new);
	termios_new.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_new);
	tcsetattr(0, 0, &termios_new);
}
