/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hell_lexer2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:27:43 by lwilliam          #+#    #+#             */
/*   Updated: 2023/02/18 16:25:29 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	key_len(char *str)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != '=')
		;
	return (i);
}

int	env_name_len(char *str, int bool)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (str[++i] && str[i] != '$')
		;
	while (str[++i] && str[i] != ' ' && str[i] != '\'' && str[i] != '"')
		++count;
	if (!bool)
		return (count);
	return (i);
}

char	*expand_helper(char *str, t_minihell *mini)
{
	char	*tmp1;
	char	*tmp2;
	char	*sub;
	char	*ret;
	int		i;

	i = -1;
	while (str[++i] && str[i] != '$')
		;
	tmp1 = ft_substr(str, 0, i);
	sub = ft_substr(str, i + 1, env_name_len(str, 0));
	tmp2 = strjoin_helper(tmp1, get_env(mini->env_ll, sub), 1, 0);
	free (sub);
	tmp1 = ft_substr(str, env_name_len(str, 1), ft_strlen(str));
	ret = strjoin_helper(tmp2, tmp1, 1, 1);
	return (ret);
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

int	len_count(char *str)
{
	int	i;

	i = 0;
	if (!str || str[i] == ' ' || !str[i])
		return (0);
	while (str[i] != ' ' && str[i])
	{
		if (str[i] == '"')
			while (str[++i] != '"' && str[i])
				;
		else if (str[i] == '\'')
			while (str[++i] != '\'' && str[i])
				;
			++i;
	}
	return (i);
}
