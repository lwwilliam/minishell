/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hell_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:27:16 by lwilliam          #+#    #+#             */
/*   Updated: 2023/03/17 00:44:28 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_init(char **in)
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
		free(key_value);
		tail = env;
	}
	while (in[++x])
	{
		key_value = ft_split(in[x], '=');
		env = list_create(key_value[0], key_value[1]);
		insert(&tail->next, env);
		free(key_value);
		tail = env;
	}
	tail->next = NULL;
	return (head);
}

void	print_env(t_env *env_ll)
{
	while (env_ll != NULL)
	{
		if (env_ll->print == 0)
			printf("%s=%s\n", env_ll->key, env_ll->value);
		env_ll = env_ll->next;
	}
}

char	*get_env(t_env *env_ll, char *what)
{
	char	*tmp;

	tmp = "";
	while (env_ll != NULL)
	{
		if (!ft_strncmp(env_ll->key, what, ft_strlen(what) + 1))
		{
			tmp = env_ll->value;
			break ;
		}
		env_ll = env_ll->next;
	}
	return (tmp);
}
