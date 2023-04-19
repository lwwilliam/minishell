/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hell_seperate2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wting <wting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:48:49 by wting             #+#    #+#             */
/*   Updated: 2023/03/10 20:16:51 by wting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_spaces_helper(char **str, int *ret, char c)
{
	*ret += 2;
	while (**str && **str == c)
		++*str;
}

int	count_spaces(char *str)
{
	int	ret;

	ret = 0;
	while (*str)
	{
		if (*str == '<')
			count_spaces_helper(&str, &ret, '<');
		else if (*str == '>')
			count_spaces_helper(&str, &ret, '>');
		else if (*str == '|')
			count_spaces_helper(&str, &ret, '|');
		else
			++str;
	}
	return (ret);
}

int	find_set(char c)
{
	char	*charset;
	int		i;

	charset = "><|";
	i = 0;
	if (!charset || !c)
		return (0);
	while (charset[i])
	{
		if (charset[i] == c)
			return (charset[i]);
		++i;
	}
	return (0);
}
