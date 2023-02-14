/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hell_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:27:16 by lwilliam          #+#    #+#             */
/*   Updated: 2023/02/14 21:06:27 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_init(t_minihell *mini, char **in)
{
	int		x;
	t_env	*head;
	t_env	*tail;
	t_env	*env;
	char	**key_value;

	x = 0;
	if (in[x])
	{
		key_value = ft_split(in[x], '=');
		env = list_create(key_value[0], key_value[1]);
		insert(&head, env);
		tail = env;
		x++;
	}
	while (in[x])
	{
		key_value = ft_split(in[x], '=');
		env = list_create(key_value[0], key_value[1]);
		x++;
		insert(&tail->next, env);
		tail = env;
	}
	free_funct(key_value);
	return (head);
}

void	print_env(t_env *env_ll, t_minihell *mini)
{
	while (env_ll != NULL)
	{
		printf("%s=%s\n", env_ll->key, env_ll->value);
		env_ll = env_ll->next;
	}
}
