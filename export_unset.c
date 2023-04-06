/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:18:51 by lwilliam          #+#    #+#             */
/*   Updated: 2023/04/06 17:43:40 by lwilliam         ###   ########.fr       */
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
		if (ft_strchr(mini->input_arr[x], '_'))
			err = 1;
		if (err == 0 && !ft_strncmp(mini->input_arr[x], mini->env_ll->key,
				ft_strlen(mini->input_arr[x]) + 1))
			remove_head_node(&mini->env_ll);
		if (err == 0)
			remove_node(&mini->env_ll, mini->input_arr[x]);
	}
	return (0);
}

int	check_exist(t_env *env_ll, char *key, char *value, int yes_no)
{
	if (key[0] == '_')
		return (1);
	while (env_ll != NULL)
	{
		if (!ft_strncmp(env_ll->key, key, ft_strlen(key) + 1) && yes_no == 0)
		{
			free(env_ll->value);
			free(key);
			env_ll->value = value;
			env_ll->print = 0;
			return (1);
		}
		env_ll = env_ll->next;
	}
	return (0);
}

void	export_equal(t_minihell *mini, t_env *env)
{
	char	x;
	t_env	*ll;

	x = 33;
	(void) mini;
	while (x < 127)
	{
		ll = env;
		while (ll != NULL)
		{
			if (ll->key[0] == x)
			{
				if (ll->print == 0)
					printf("declare -x %s=\"%s\"\n", ll->key, ll->value);
				else
					printf("declare -x %s\n", ll->key);
			}
			ll = ll->next;
		}
		x++;
	}
}

int	export(t_minihell *mini)
{
	char	*key;
	char	*value;
	int		x;
	int		err;
	int		yes_no;

	x = 0;
	if (!mini->input_arr[1])
		export_equal(mini, mini->env_ll);
	while (mini->input_arr[++x])
	{
		printf("%s\n", mini->input_arr[x]);
		yes_no = 0;
		if (!ft_strchr(mini->input_arr[x], '='))
			yes_no = 1;
		key = ft_substr(mini->input_arr[x], 0, key_len(mini->input_arr[x]));
		value = ft_substr(mini->input_arr[x], key_len(mini->input_arr[x]) + 1,
				ft_strlen(mini->input_arr[x]) - key_len(mini->input_arr[x]));
		err = check_exist(mini->env_ll, key, value, yes_no);
		if (!ft_isalpha(key[0]))
			err = export_error(mini->input_arr[x], key, value);
		if (err == 0)
			add_node_end(mini->env_ll, key, value, yes_no);
	}
	return (0);
}
