/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hell_seperate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:42:06 by wting             #+#    #+#             */
/*   Updated: 2023/03/16 16:05:54 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	increment_copy(char **str, char **ret, int *i)
{
	(*ret)[(*i)++] = **str;
	++*str;
}

void	seperate_helper(char **str, char **ret, int *i)
{
	while (**str && (**str == '\'' || **str == '"'))
	{
		if (**str == '\'')
		{
			increment_copy(str, ret, i);
			while (**str && **str != '\'')
			{
				increment_copy(str, ret, i);
			}
			increment_copy(str, ret, i);
		}
		else if (**str == '"')
		{
			increment_copy(str, ret, i);
			while (**str && **str != '"')
			{
				increment_copy(str, ret, i);
			}
			increment_copy(str, ret, i);
		}
	}
	return ;
}

void	add_spaces(char **ret, char **str, int *i, char c)
{
	(*ret)[*i] = ' ';
	++*i;
	while (**str && **str == c)
	{
		(*ret)[(*i)++] = c;
		++*str;
	}
	(*ret)[(*i)++] = ' ';
}

char	*seperate(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = malloc(sizeof(char) * (ft_strlen(str) + count_spaces(str) + 1));
	while (*str)
	{
		seperate_helper(&str, &ret, &i);
		if (find_set(*str))
			add_spaces(&ret, &str, &i, find_set(*str));
		else if (*str)
		{
			ret[i++] = *str;
			++str;
		}
	}
	ret[i] = '\0';
	return (ret);
}
