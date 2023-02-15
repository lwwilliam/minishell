/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hell_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:27:16 by lwilliam          #+#    #+#             */
/*   Updated: 2023/02/15 20:18:45 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//some issues with the ls_colors env did not work cuz ft_split
//also need to handle if key_value[1] is null
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
		tail = env;
	}
	while (in[++x])
	{
		key_value = ft_split(in[x], '=');
		env = list_create(key_value[0], key_value[1]);
		insert(&tail->next, env);
		tail = env;
	}
	return (head);
}

void	print_env(t_env *env_ll)
{
	while (env_ll != NULL)
	{
		printf("%s=%s\n", env_ll->key, env_ll->value);
		env_ll = env_ll->next;
	}
}

char	*get_env(t_env *env_ll, char *what)
{
	int		x;
	char	*tmp;
	char	*the_value;

	x = 0;
	tmp = "(null)";
	while (env_ll != NULL)
	{
		if (!ft_strncmp(env_ll->key, what, ft_strlen(what)))
			tmp = env_ll->value;
		env_ll = env_ll->next;
	}
	if (tmp)
	{
		the_value = malloc(sizeof(char) * ft_strlen(tmp));
		while (tmp[x])
		{
			the_value[x] = tmp[x];
			x++;
		}
	}
	the_value[x] = '\0';
	return (the_value);
}
