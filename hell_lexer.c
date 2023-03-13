/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hell_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:45:39 by wting             #+#    #+#             */
/*   Updated: 2023/03/14 01:12:02 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quote_helper(char *str, char *ret, int *i, int *j)
{
	if (str[*i] == '\'')
		while (str[++*i] && str[*i] != '\'')
			ret[(*j)++] = str[*i];
	else if (str[*i] == '"')
		while (str[++*i] && str[*i] != '"')
			ret[(*j)++] = str[*i];
	else
		ret[(*j)++] = str[*i];
	++*i;
}

char	*remove_quote(char *str, int len)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	while (str[i])
		remove_quote_helper(str, ret, &i, &j);
	ret[j] = 0;
	free (str);
	return (ret);
}

void	word_count_helper(char **str)
{
	if (**str == '"')
	{
		++*str;
		while (**str && **str != '"')
			++*str;
	}
	else if (**str && **str == '\'')
	{
		++*str;
		while (**str && **str != '\'')
			++*str;
	}
	else
		++*str;
}

int	word_count(char *str)
{
	int	ret;

	ret = 0;
	while (*str)
	{
		while (*str && *str == ' ')
			++str;
		++ret;
		while (*str && *str != ' ')
		{
			word_count_helper(&str);
		}
	}
	return (ret);
}

char	**lexer(char *str, t_minihell *mini)
{
	char	**ret;
	int		i;
	char	*tmp;

	(void) mini;
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
			tmp = ft_substr(str, 0, (len_count(str)));
			ret[i] = remove_quote(tmp, (len_count(str)));
			str += len_count(str);
			++i;
		}
		else
			++str;
	}
	ret[i] = NULL;
	return (ret);
}
