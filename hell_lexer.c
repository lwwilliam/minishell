/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hell_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wting <wting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:45:39 by wting             #+#    #+#             */
/*   Updated: 2023/02/15 22:05:10 by wting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*expand(char *str, t_minihell *mini)
{
	int		i;
	char	*ret;
	int		count;
	char	*tmp;
	
	ret = NULL;
	tmp = NULL;
	count = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && count == 0)
		{
			ret = expand_helper(str, mini);
			++count;
		}
		else if (str[i] == '$')
		{
			tmp = expand_helper(ret, mini);
			free (ret);
			ret = ft_strdup(tmp);
			free (tmp);
			++count;
		}
		// printf("loop %d:  tmp=%s | ret=%s\n", count, tmp, ret);
	}
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

int	word_count(char *str)
{
	int	i;
	int	ret;

	ret = 0;
	i = -1;
	while (str[++i])
	{
		while (str[i] == ' ' && str[i])
			++i;
		++ret;
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
	}
	return (ret);
}

char	**lexer(char *str, t_minihell *mini)
{
	char	**ret;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	ret = malloc(sizeof(char *) * (word_count(str) + 1));
	if (!ret)
		return (NULL);
	while (*str)
	{
		if (len_count(str))
		{
			ret[i] = ft_substr(str, 0, (len_count(str)));
			str += len_count(str);
			++i;
		}
		else
			++str;
	}
	ret[i] = NULL;
	return (ret);
}
