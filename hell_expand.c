/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hell_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:03:25 by wting             #+#    #+#             */
/*   Updated: 2023/03/16 16:02:57 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exp_dollar(int *i, int *count, char **ret, t_minihell *mini)
{
	char	*tmp;
	char	*str;

	str = mini->yes;
	if (str[*i] == '$' && !*count && str[(*i) + 1] && str[(*i) + 1] != ' ')
	{
		*ret = expand_helper(str, mini);
		++*count;
	}
	else if (str[*i] == '$' && str[*i + 1] && str[*i + 1] != ' ')
	{
		tmp = expand_helper(*ret, mini);
		free (*ret);
		*ret = ft_strdup(tmp);
		free (tmp);
		++*count;
	}
}

char	*expand(char *str, t_minihell *mini)
{
	int		i;
	char	*ret;
	int		count;
	char	*tmp;

	ret = NULL;
	count = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			while (str[++i] && str[i] != '\'')
				;
		if (str[i] == '"')
		{
			while (str[++i] && str[i] != '"')
				exp_dollar(&i, &count, &ret, mini);
		}
		exp_dollar(&i, &count, &ret, mini);
	}
	if (!ret)
		ret = ft_strdup(str);
	return (ret);
}
