/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:23:59 by lwilliam          #+#    #+#             */
/*   Updated: 2023/02/22 21:40:35 by lwilliam         ###   ########.fr       */
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

void	end(t_minihell *mini)
{
	rl_clear_history();
	freelist(&mini->env_ll);
	printf("exit\n");
	system("leaks Minishell");
	exit(0);
}

int	export_error(char *in, char *key, char *value)
{
	printf("Minishell: export: '%s': %s\n", in, VALID);
	free(value);
	free(key);
	return (1);
}
