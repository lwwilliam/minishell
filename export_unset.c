/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:18:51 by lwilliam          #+#    #+#             */
/*   Updated: 2023/02/17 19:40:08 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(t_minihell *mini)
{
	int	x;
	int	err;

	x = 0;
	while (mini->input_arr[++x])
	{
		err = 0;
		if (ft_strchr(mini->input_arr[x], '='))
		{
			printf("Minishell: unset: '%s': not a valid identifier\n",
				mini->input_arr[x]);
			err = 1;
		}
		if (err == 0 && !ft_strncmp(mini->input_arr[x], mini->env_ll->key,
				ft_strlen(mini->input_arr[x])))
			remove_head_node(&mini->env_ll);
		if (err == 0)
			remove_node(&mini->env_ll, mini->input_arr[x]);
	}
	return (0);
}

int	check_exist(t_env *env_ll, char *key, char *value)
{
	while (env_ll != NULL)
	{
		if (!ft_strncmp(env_ll->key, key, ft_strlen(key)))
		{
			env_ll->value = value;
			return (1);
		}
		env_ll = env_ll->next;
	}
	return (0);
}

void	export_equal(t_minihell *mini, t_env *ll)
{
	(void) mini;
	while (ll != NULL)
	{
		printf("declare -x %s=\"%s\"\n", ll->key, ll->value);
		ll = ll->next;
	}
}

int	key_len(char *str)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != '=')
		;
	return (i);
}

int	export(t_minihell *mini)
{
	char	*key;
	char	*value;
	int		x;
	int		err;

	x = 0;
	if (!mini->input_arr[1])
		export_equal(mini, mini->env_ll);
	while (mini->input_arr[++x])
	{
		if (!ft_strchr(mini->input_arr[x], '='))
			return (1);
		key = ft_substr(mini->input_arr[x], 0, key_len(mini->input_arr[x]));
		value = ft_substr(mini->input_arr[x], key_len(mini->input_arr[x]) + 1,
				ft_strlen(mini->input_arr[x]) - key_len(mini->input_arr[x]));
		err = check_exist(mini->env_ll, key, value);
		if (ft_isdigit(key[0]))
		{
			printf("Minishell: export: '%s': %s\n", mini->input_arr[x], VALID);
			err = 1;
		}
		if (err == 0)
			add_node_end(mini->env_ll, key, value);
	}
	return (0);
}
