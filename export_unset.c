/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:18:51 by lwilliam          #+#    #+#             */
/*   Updated: 2023/02/16 20:12:54 by lwilliam         ###   ########.fr       */
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

int	export(t_minihell *mini)
{
	char	**param;
	int		x;
	int		err;

	x = 0;
	while (mini->input_arr[++x])
	{
		err = 0;
		if (!ft_strchr(mini->input_arr[x], '='))
			return (1);
		param = ft_split(mini->input_arr[x], '=');
		if (ft_isdigit(param[0][0]))
		{
			printf("Minishell: export: '%s': not a valid identifier\n",
				mini->input_arr[x]);
			err = 1;
		}
		if (err == 0)
			add_node_end(mini->env_ll, param[0], param[1]);
	}
	return (0);
}
