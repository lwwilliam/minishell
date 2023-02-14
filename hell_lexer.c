/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hell_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:45:39 by wting             #+#    #+#             */
/*   Updated: 2023/02/14 18:22:13 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		else
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
					printf("in: %c\n", str[i]);
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
