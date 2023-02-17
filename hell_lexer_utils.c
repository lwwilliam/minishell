/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hell_lexer_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wting <wting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:27:07 by wting             #+#    #+#             */
/*   Updated: 2023/02/17 14:26:13 by wting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_helper(char *str, t_minihell *mini)
{
	char	*tmp1;
	char	*tmp2;
	char	*ret;
	int		i;

	i = -1;
	while (str[++i] && str[i] != '$')
		;
	tmp1 = ft_substr(str, 0, i);
	tmp2 = strjoin_helper(tmp1, find_env(str + i, mini), 1, 0);
	tmp1 = ft_substr(str, env_name_len(str), ft_strlen(str));
	printf("strjoin:%s\n", tmp1);
	ret = strjoin_helper(tmp2, tmp1, 1, 1);
	return (ret);
}

int	env_name_len(char *str)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != '$')
		;
	while (str[++i] && str[i] != ' ' && str[i] != '\'' && str[i] != '"')
		;
	return (i);
}

int	env_key_len(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '=' && str[i])
		;
	return (i);
}

char	*find_env(char	*str, t_minihell *mini)
{
	int	i;
	int	j;

	if (!str)
		return (NULL);
	++str;
	i = -1;
	while (str[++i] && str[i] != ' ' && str[i] != '"' && str[i] != '\'')
		;
	j = -1;
	while (mini->env_arr[++j])
	{
		if (!ft_strncmp(mini->env_arr[j], str, i) && \
				i == env_key_len(mini->env_arr[j]))
			return (mini->env_arr[j] + i + 1);
	}
	return ("");
}

char	*strjoin_helper(char *str1, char *str2, int free1, int free2)
{
	char	*ret;

	if (!str1 || !str2)
		return (NULL);
	ret = ft_strjoin(str1, str2);
	if (free1)
		free(str1);
	if (free2)
		free(str2);
	return (ret);
}
