/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:27:18 by lwilliam          #+#    #+#             */
/*   Updated: 2023/03/07 12:35:33 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count(t_env *env)
{
	int	x;

	x = 0;
	while (env != NULL)
	{
		x++;
		env = env->next;
	}
	return (x);
}

char	**env_2d(t_env *env)
{
	char	**td_arr;
	char	*str1;
	char	*str2;
	int		x;

	x = 0;
	td_arr = malloc(sizeof(char *) * (count(env) + 1));
	while (env != NULL)
	{
		str1 = ft_strdup(env->key);
		str2 = strjoin_helper(str1, "=", 1, 0);
		td_arr[x] = strjoin_helper(str2, env->value, 1, 0);
		x++;
		env = env->next;
	}
	td_arr[x] = NULL;
	return (td_arr);
}
